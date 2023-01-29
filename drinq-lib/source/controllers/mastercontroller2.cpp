#include "mastercontroller2.h"

#include <QSettings>

#include <models/drink.h>
#include <models/clientsearch.h>
#include <models/recentactivity.h>
#include "databasecontroller.h"

#include "partycontroller.h"

using namespace drinq::models;

namespace drinq {
namespace controllers {

const QString USERNAME_KEY = "username";
const QString USER_EMAIL_KEY = "email";

MasterController2::MasterController2(QObject *parent,
                                     DatabaseControllerInterface *dbController,
                                     PartyController* _partyController,
                                     QSettings* settings)
    : QObject(parent),
      databaseController(dbController), partyController(_partyController), m_settings(settings)
{
    m_user_missing = m_settings->value(USERNAME_KEY).toString().isEmpty() ||
                     m_settings->value(USER_EMAIL_KEY).toString().isEmpty();

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
    m_party_title = name;
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

qint64 MasterController2::secondsSinceLastDrink()
{
    //This assumes drink time cannot be changed and last id is the most recent
    const QVariant last_drink_id = databaseController->getLastId("drink");

    if(last_drink_id.isNull())
    {
        return -1;
    }

    auto* drink = new drinq::models::Drink2(this);
    drink->setId(last_drink_id);
    databaseController->get(*drink);
    drink->update(drink->toJson());
    const qint64 diff_sec = drink->m_timestamp.secsTo(QDateTime::currentDateTime());
    return diff_sec;
}

void MasterController2::registerUser(const QString &username, const QString &email)
{
    if(username.isEmpty() || email.isEmpty())
    {
        return;
    }

    m_settings->setValue(USERNAME_KEY, username);
    m_settings->setValue(USER_EMAIL_KEY, email);

    m_user_missing = false;
    emit ui_user_missing_changed();
}

}
}
