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

void DrinkController::addDrinkType()
{
    //todo:
    emit drinkTypesChanged();
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
    QVector<QPair<QString, unsigned int>> drink_types = {
        {"wine", 150},
        {"beer", 500},
        {"vodka", 25},
        {"vodka", 50}
    };

    for(auto dt : drink_types)
    {
        drinq::models::DrinkType newDrink;
        newDrink.setName(dt.first);
        newDrink.setDefaultAmountMl(dt.second);
        if(m_db->create(newDrink))
        {
            qDebug() << "Created drink type " << dt.first << " with default amount " << dt.second;
        }
        else
        {
            qDebug() << "Creation of drink type " << dt.first << " failed";
        }
    }
}

}
