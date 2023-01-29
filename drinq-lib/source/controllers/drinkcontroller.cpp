#include "drinkcontroller.h"

#include "databasecontrollerinterface.h"

#include "models/drink.h"

//TODO enable this
//#include "external/sqlite_orm.h"

#include <QSettings>
#include <QDebug>

namespace drinq::controllers {

const QString DRINK_TYPES_IDS_ORDER = "drink_types_ids_order";
const QString DRINK_TYPE_KEY = "drink_type_id";
const QString DRINK_AMOUNT_KEY = "drink_amount_ml";

DrinkController::DrinkController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db, QSettings* settings)
    : QObject(parent), m_db(db), m_settings(settings)
{
    loadDrinkTypeSettings();
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

void DrinkController::updateDrinkType(drinq::models::DrinkType* drink_type)
{
    if(!drink_type)
    {
        qDebug() << "Invalid drink type";
        return;
    }

    qDebug() << "Valid drink type: " << drink_type->toJson();
}

void DrinkController::setCurrentDrinkProperties(int index, unsigned int amount_ml)
{
    m_currentDrinkTypeIndex = index;
    m_currentDrinkAmountMl = amount_ml;

    if(index >= m_drinkTypes.size())
    {
        qDebug() << "Incorrect index supplied: " << index;
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

    //push added to the first place by rolling all in m_drink_types
    const auto currentDrinkType = m_drinkTypes[index];
    m_drinkTypes.removeAt(index);
    m_drinkTypes.prepend(currentDrinkType);
    emit drinkTypesChanged();

    QStringList drinkTypesIds;
    for(const auto& drinkType : m_drinkTypes)
    {
        drinkTypesIds.append(drinkType->m_id.toString());
    }

    qDebug() << "Settings drinks tpyes ids to " << drinkTypesIds.join(',');

    m_settings->setValue(DRINK_TYPES_IDS_ORDER, drinkTypesIds.join(','));
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

void DrinkController::loadDrinkTypeSettings()
{
    auto drink_types = m_db->getAll(drinq::models::DrinkType{this});

    if(drink_types.isEmpty())
    {
        createDrinkTypes();
        drink_types = m_db->getAll(drinq::models::DrinkType{this});
    }

    std::reverse(drink_types.begin(), drink_types.end());

    if(m_settings->contains(DRINK_TYPES_IDS_ORDER) && m_settings->contains(DRINK_AMOUNT_KEY))
    {
        const auto drink_types_ids = m_settings->value(DRINK_TYPES_IDS_ORDER).toString().split(',');
        if(drink_types_ids.size() == drink_types.size())
        {
            QMap<QVariant, drinq::models::DrinkType*> drink_type_by_id;
            for(const auto& dt : qAsConst(drink_types))
            {
                drink_type_by_id[dt.m_data["id"]] = new drinq::models::DrinkType(dt.toJson(), this);
            }

            for(const auto& dti : drink_types_ids)
            {
                if(!drink_type_by_id.contains(dti))
                {
                    qDebug() << "ERROR while loading drink types from settings";
                    continue;
                }

                m_drinkTypes.append(drink_type_by_id[dti]);
            }

            qDebug() << "Sunny day setting drink types";
            setCurrentDrinkProperties(0, m_settings->value(DRINK_AMOUNT_KEY).toInt());
            return;
        }
    }

    qDebug() << "Fallback setting drink types";
    for(const auto& dt : drink_types)
    {
        m_drinkTypes.append(new drinq::models::DrinkType(dt.toJson(), this));
    }

    setCurrentDrinkProperties(0, m_drinkTypes.first()->m_default_amount_ml);

    emit drinkTypesChanged();
}

}
