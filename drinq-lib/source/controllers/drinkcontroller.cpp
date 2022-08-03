#include "drinkcontroller.h"

#include "databasecontrollerinterface.h"

#include "models/drink.h"

//TODO enable this
//#include "external/sqlite_orm.h"

#include <QSettings>
#include <QDebug>

namespace drinq::controllers {

const QString DRINK_TYPE_KEY = "drink_type_id";
const QString DRINK_AMOUNT_KEY = "drink_amount_ml";

DrinkController::DrinkController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db, QSettings* settings)
    : QObject(parent), m_db(db), m_settings(settings)
{
    auto drink_types = m_db->getAll(drinq::models::DrinkType{this});

    if(drink_types.isEmpty())
    {
        createDrinkTypes();
        drink_types = m_db->getAll(drinq::models::DrinkType{this});
    }


    for(const auto& dt : drink_types)
    {
        m_drinkTypes.append(new drinq::models::DrinkType(dt.toJson(), this));
    }

    if(m_settings->contains(DRINK_TYPE_KEY) && m_settings->contains(DRINK_AMOUNT_KEY))
    {
        setCurrentDrinkProperties(m_settings->value(DRINK_TYPE_KEY).toInt(), m_settings->value(DRINK_AMOUNT_KEY).toInt());
    }
    else
    {
        if(!drink_types.isEmpty())
        {
            setCurrentDrinkProperties(0, m_drinkTypes.first()->m_default_amount_ml);
        }
        else
        {
            qDebug() << "No drink types defined";
        }
    }
    emit drinkTypesChanged();
}

DrinkController::~DrinkController()
{

}

QQmlListProperty<drinq::models::DrinkType> DrinkController::ui_drinkTypes()
{
    return QQmlListProperty<drinq::models::DrinkType>(this, m_drinkTypes);
}

QString DrinkController::type(QVariant id)
{
    qDebug() << "Type for " << id.toString();

    if(const auto it = std::find_if(m_drinkTypes.begin(), m_drinkTypes.end(), [id](drinq::models::DrinkType* dt){
//        qDebug() << "Comparing id with obj id " << id.toString() << " " << dt->m_id.toString() << "(" << dt->m_name << ")";
        return dt->m_id == id;
    }); it != m_drinkTypes.end())
    {
        return (*it)->m_name;
    }

    return "Unknown";
}

//bool DrinkController::addDrink()
//{

//    newDrink.setAmountMl(2137);
//    qDebug() << "Updating drink";
//    qDebug() << "Before " << newDrink.toJson();
//    qDebug() << "Result " << m_db->update(newDrink);
//    qDebug() << "After " << newDrink.toJson();

//    qDebug() << "Reading drink";
//    drinq::models::Drink2 readDrink;
//    readDrink.setId(newDrink.m_id);
//    qDebug() << "Result " <<  m_db->get(readDrink);

//    qDebug() << "Read drink " << readDrink.toJson();

//    qDebug() << "Removing drink";
//    qDebug() << "Result " <<  m_db->remove(readDrink);

//    auto result = m_db->createRow("drink", newDrink.toJson());

//    qDebug() << "RESULT " << result;

//    return true;
//}

//void DrinkController::setPartyId(const QVariant &partyId)
//{
//    m_currentPartyId = partyId;
//}

void DrinkController::addDrinkType(const QString &name, int default_amount, drinq::models::DrinkType::ConsumptionType type)
{
    auto newDrinkType = new drinq::models::DrinkType{this};
    newDrinkType->setName(name);
    newDrinkType->setDefaultAmountMl(default_amount);
    newDrinkType->setConsumptionType(type);

    if(m_db->create(*newDrinkType))
    {
        m_drinkTypes.append(newDrinkType);
        qDebug() << "Created new drink type " << newDrinkType->toJson();
        emit drinkTypesChanged();
    }
    else
    {
        qDebug() << "Unable to create new drink type";
    }
}

void DrinkController::setCurrentDrinkProperties(int index, unsigned int amount_ml)
{
    m_currentDrinkTypeIndex = index;
    m_currentDrinkAmountMl = amount_ml;

    if(index >= m_drinkTypes.size())
    {
        qDebug() << "Incorrect index supplied";
        index = 0;
    }

    m_currentDrinkType = m_drinkTypes[index]->m_name;
    m_currentDrinkTypeId = m_drinkTypes[index]->m_id;

    qDebug() << "index " << index << " amount " << amount_ml;

    m_settings->setValue(DRINK_TYPE_KEY, m_currentDrinkTypeIndex);
    m_settings->setValue(DRINK_AMOUNT_KEY, m_currentDrinkAmountMl);

    emit currentDrinkAmountMlChanged();
    emit currentDrinkTypeIndexChanged();
    emit currentDrinkTypeChanged();
}

void DrinkController::createDrinkTypes()
{
    using ConsumptionType = drinq::models::DrinkType::ConsumptionType;

    QVector<std::tuple<QString, unsigned int, ConsumptionType>> drink_types = {
        {"wine", 150, ConsumptionType::Long},
        {"beer", 500, ConsumptionType::Long},
        {"vodka", 25, ConsumptionType::Shot},
        {"vodka", 50, ConsumptionType::Long}
    };

    for(auto dt : drink_types)
    {
        drinq::models::DrinkType newDrink;
        newDrink.setName(std::get<0>(dt));
        newDrink.setDefaultAmountMl(std::get<1>(dt));
        newDrink.setConsumptionType(std::get<2>(dt));

        if(m_db->create(newDrink))
        {
            qDebug() << "Created drink type " << std::get<0>(dt)
                     << " with default amount " << std::get<1>(dt)
                     << " and consumption type " << (std::get<2>(dt) == ConsumptionType::Long ? "Long" : "Shot");
        }
        else
        {
            qDebug() << "Creation of drink type " << std::get<0>(dt) << " failed";
        }
    }
}

}
