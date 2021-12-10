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
    unsigned long party_id = getLastPartyId();

    qDebug() << "Latest party id " << party_id;

    drinq::models::Drink2 newDrink;
    newDrink.setPartyId(party_id);

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

unsigned int DrinkController::getLastPartyId()
{
    auto party = m_db->readParty();

    if(!party.isEmpty())
    {
        drinq::models::Party2 dbParty(this, party);
        return dbParty.m_id.toInt();
    }

    drinq::models::Party2 new_party(this);
    m_db->createRow("party", new_party.toJson());
    party = m_db->readParty();

    return party["id"].toVariant().toUInt();
}

bool DrinkController::resetCounter()
{
    qDebug() << "Creating new party";

    drinq::models::Party2 newParty;
    m_db->createRow("party", newParty.toJson());

    qDebug() << "Resetting counter";

    return true;
}
