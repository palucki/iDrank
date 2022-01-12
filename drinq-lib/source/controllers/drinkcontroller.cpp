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
//    auto lastId = m_db->getLastId("drink");
//    if(lastId.isNull())
//    {
//        qDebug() << "NO drinks";
//    }
//    else
//    {
//        qDebug() << "Last drink id " << lastId;
//    }

    auto drink_types = m_db->getAll(drinq::models::DrinkType{this});

    qDebug() << "Found " << drink_types.size() << " drink types";

    for(const auto& dt : drink_types)
    {
//        qDebug() << drink_type.m_name << " default amount: " << drink_type.m_default_amount_ml;
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
}

DrinkController::~DrinkController()
{

}

QQmlListProperty<drinq::models::DrinkType> DrinkController::ui_drinkTypes()
{
    return QQmlListProperty<drinq::models::DrinkType>(this, m_drinkTypes);
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

    qDebug() << "index " << index << " amount " << amount_ml;

    m_settings->setValue("drink_type_id", m_currentDrinkTypeIndex);
    m_settings->setValue("drink_amount_ml", m_currentDrinkAmountMl);
}

}
