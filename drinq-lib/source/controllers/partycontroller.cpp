#include "partycontroller.h"

#include "databasecontrollerinterface.h"

#include "controllers/drinkcontroller.h"
#include "models/drink.h"

#include <QDebug>

PartyController::PartyController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db, drinq::controllers::DrinkController *drinksController)
    : QObject(parent), m_db(db)
{
    if(drinksController)
    {
        connect(drinksController, &drinq::controllers::DrinkController::drinkAdded, this, [this]{
            qDebug() << "PartyController -> drink added";
            setDrinksCount(m_current_drinks_count + 1);
        });
    }

    auto lastId = m_db->getLastId("party");

    m_current_party = std::make_unique<drinq::models::Party2>();
    m_current_party->setId(lastId);
    m_db->get(*m_current_party);

    //fix to keep state up to date
//    m_current_party->update();

    qDebug() << "Latest party " << m_current_party->toJson();

    if(isPartyStarted())
    {
        setDrinksCount(m_db->count(drinq::models::Drink2{this}, "WHERE party_id = " + lastId.toString()));
    }

    qDebug() << "drinks count: " << m_current_drinks_count;
}

PartyController::~PartyController()
{
}

bool PartyController::isPartyStarted()
{
    return m_current_party->m_data["ended"].toDateTime().isNull();
//TODO: fix after propoer update() methods are added for all classes deriving from enetity
//    return m_current_party->m_ended.isNull();
}

void PartyController::startParty()
{
    m_current_party = std::make_unique<drinq::models::Party2>();
    setDrinksCount(0);
    m_db->create(*m_current_party);
}

void PartyController::endParty()
{
    m_current_party->setEnded(QDateTime::currentDateTime());
    setDrinksCount(0);
    m_db->update(*m_current_party);
}

void PartyController::setPartyName(const QString &name)
{
    m_current_party->setName(name);
    m_db->update(*m_current_party);
}

QVariant PartyController::currentPartyId()
{
    return m_current_party->m_id;
}

void PartyController::setDrinksCount(int count)
{
    qDebug() << "CURRENT COUnT " << count;
    m_current_drinks_count = count;

    emit ui_drinks_countChanged(m_current_drinks_count);
}
