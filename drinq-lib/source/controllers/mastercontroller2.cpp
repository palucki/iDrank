#include "mastercontroller2.h"

#include <models/drink.h>
#include <models/clientsearch.h>
#include <models/recentactivity.h>
#include "databasecontroller.h"

#include "partycontroller.h"

using namespace drinq::models;

namespace drinq {
namespace controllers {


MasterController2::MasterController2(QObject *parent,
                                     DatabaseControllerInterface *dbController,
                                     PartyController* _partyController)
    : QObject(parent),
      databaseController(dbController), partyController(_partyController)
{
    auto parties = databaseController->getAll(drinq::models::Party2{this});

    qDebug() << "Found " << parties.size() << " parties";

    for(const auto& p : parties)
    {
//        qDebug() << drink_type.m_name << " default amount: " << drink_type.m_default_amount_ml;
        m_parties.append(new drinq::models::Party2(p.toJson(), this));
    }

    std::sort(m_parties.begin(), m_parties.end(), [](drinq::models::Party2* lhs, drinq::models::Party2* rhs){
        return rhs->m_started < lhs->m_started;
    });

    auto lastId = databaseController->getLastId("party");
    if(lastId.isNull())
    {
        qDebug() << "No parties yet";
    }
    else
    {
        m_current_party = new drinq::models::Party2(this);
        m_current_party->setId(lastId);
        partyController->setPartyId(lastId);
        databaseController->get(*m_current_party);

        qDebug() << "Latest party " << m_current_party->toJson();

        m_current_party->update(m_current_party->toJson());

        if(isPartyStarted())
        {
            m_party_started = true;
            m_party_title = m_current_party->m_name;
        }
    }
}

MasterController2::~MasterController2()
{
}

QQmlListProperty<Party2> MasterController2::ui_parties()
{
    qDebug() << "Getting parties size: " << m_parties.size();
    return QQmlListProperty<drinq::models::Party2>(this, m_parties);
}

void MasterController2::setPartyName(const QString &name)
{
    m_current_party->setName(name);

    emit ui_party_titleChanged();
}

bool MasterController2::isPartyStarted()
{
     return m_current_party->m_data["ended"].toDateTime().isNull();
}

void MasterController2::startParty(const QString& name)
{
    qDebug() << "Starting party " << name;

    m_current_party = new drinq::models::Party2(this);
    setPartyName(name);
    if(databaseController->create(*m_current_party))
    {
        m_parties.append(m_current_party);
        std::sort(m_parties.begin(), m_parties.end(), [](drinq::models::Party2* lhs, drinq::models::Party2* rhs){
            return rhs->m_started < lhs->m_started;
        });
    }
    else
    {
        qDebug() << "Error! Unable to create party";
    }

    partyController->setPartyId(m_current_party->m_id);
    partyController->startParty();
    m_party_started = isPartyStarted();
    emit ui_party_startedChanged();
    emit ui_partiesChanged();
}

void MasterController2::endParty()
{
    partyController->endParty();

    m_current_party->setEnded(QDateTime::currentDateTime());
    databaseController->update(*m_current_party);

    m_party_started = isPartyStarted();
    emit ui_party_startedChanged();
    emit ui_partiesChanged();
}

}
}
