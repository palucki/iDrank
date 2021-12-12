#include "partycontroller.h"

#include "databasecontrollerinterface.h"

#include "models/drink.h"

#include <QDebug>

PartyController::PartyController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db)
    : QObject(parent), m_db(db)
{
    auto lastId = m_db->getLastId("party");

    m_current_party = std::make_unique<drinq::models::Party2>();
    m_current_party->setId(lastId);
    m_db->get(*m_current_party);

    //fix to keep state up to date
//    m_current_party->update();

    qDebug() << "Latest party " << m_current_party->toJson();
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
    m_db->create(*m_current_party);
}

void PartyController::endParty()
{
    m_current_party->setEnded(QDateTime::currentDateTime());
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
