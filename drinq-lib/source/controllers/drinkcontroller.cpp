#include "drinkcontroller.h"

#include "databasecontrollerinterface.h"

#include "models/drink.h"

//TODO enable this
//#include "external/sqlite_orm.h"

#include <QDebug>

DrinkController::DrinkController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db)
    : QObject(parent), m_db(db)
{
    auto lastId = m_db->getLastId("drink");
    if(lastId.isNull())
    {
        qDebug() << "NO drinks";
    }
    else
    {
        qDebug() << "Last drink id " << lastId;
    }

    auto drink_types = m_db->getAll(drinq::models::DrinkType{this});

    qDebug() << "Found " << drink_types.size() << " drink types";

    for(const auto& dt : drink_types)
    {
//        qDebug() << drink_type.m_name << " default amount: " << drink_type.m_default_amount_ml;
        m_drinkTypes.append(new drinq::models::DrinkType(dt.toJson()));
    }
}

DrinkController::~DrinkController()
{

}

QQmlListProperty<drinq::models::DrinkType> DrinkController::ui_drinkTypes()
{
    return QQmlListProperty<drinq::models::DrinkType>(this, m_drinkTypes);
}

bool DrinkController::addDrink()
{
    qDebug() << "Latest party id " << m_currentPartyId;

    drinq::models::Drink2 newDrink;
    newDrink.setPartyId(m_currentPartyId);

    qDebug() << "Adding drink: " << newDrink.toJson();
    qDebug() << "Result " << m_db->create(newDrink);

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

    return true;
}

void DrinkController::setPartyId(const QVariant &partyId)
{
    m_currentPartyId = partyId;
}

void DrinkController::addDrinkType()
{
    //todo:
    emit drinkTypesChanged();
}

