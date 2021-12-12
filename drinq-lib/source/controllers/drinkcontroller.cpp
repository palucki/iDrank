#include "drinkcontroller.h"

#include "databasecontrollerinterface.h"

#include "models/drink.h"

#include <QDebug>

DrinkController::DrinkController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db)
    : QObject(parent), m_db(db)
{
    auto lastId = m_db->getLastId("drinks");
    if(lastId.isNull())
    {
        qDebug() << "NO drinks";
    }
}

DrinkController::~DrinkController()
{

}

bool DrinkController::addDrink()
{
    auto partyId =  m_db->getLastId("party");
    qDebug() << "Latest party id " << partyId;

    drinq::models::Drink2 newDrink;
    newDrink.setPartyId(partyId);

    qDebug() << "Adding drink: " << newDrink.toJson();
    qDebug() << "Result " << m_db->create(newDrink);

    newDrink.setAmountMl(2137);
    qDebug() << "Updating drink";
    qDebug() << "Before " << newDrink.toJson();
    qDebug() << "Result " << m_db->update(newDrink);
    qDebug() << "After " << newDrink.toJson();

    qDebug() << "Reading drink";
    drinq::models::Drink2 readDrink;
    readDrink.setId(newDrink.m_id);
    qDebug() << "Result " <<  m_db->get(readDrink);

    qDebug() << "Read drink " << readDrink.toJson();

    qDebug() << "Removing drink";
    qDebug() << "Result " <<  m_db->remove(readDrink);

//    auto result = m_db->createRow("drink", newDrink.toJson());

//    qDebug() << "RESULT " << result;

    return true;
}

bool DrinkController::resetCounter()
{
    qDebug() << "Creating new party";

    drinq::models::Party2 newParty;
    m_db->create(newParty);

    qDebug() << "Resetting counter";

    return true;
}
