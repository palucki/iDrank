#include "partycontroller.h"

#include "databasecontrollerinterface.h"

#include "controllers/drinkcontroller.h"
#include "models/drink.h"

#include <QDebug>

PartyController::PartyController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db, drinq::controllers::DrinkController *drinksController)
    : QObject(parent), m_db(db), m_drinkController(drinksController), m_drinkProvider(db)
{
}

PartyController::~PartyController()
{
}

qint64 PartyController::secondsSinceLastDrink()
{
    if(m_drinks.empty())
    {
        return -1;
    }

    //because sorted in reverse order
    auto& last_drink = m_drinks.first();

    const qint64 diff_sec = last_drink->m_timestamp.secsTo(QDateTime::currentDateTime());
    return diff_sec;
}

void PartyController::startParty()
{
    m_drinks.clear();
    //required to update date time axis only?
    emit ui_drinksChanged();
    setDrinksCount(0);
}

void PartyController::setPartyId(QVariant id)
{
    drinq::models::Party2 party(this);
    party.setId(id);

    m_db->get(party);
    drinq::models::Party2 current_party{party.toJson()};

    m_currentPartyStarted = current_party.m_started;

    m_currentPartyId = id;

    m_drinks = m_drinkProvider.getDrinksList(id);

    qDebug() << "Found " << m_drinks.size() << " drinks. party started at " << m_currentPartyStarted;

    std::sort(m_drinks.begin(), m_drinks.end(), [](drinq::models::Drink2* lhs, drinq::models::Drink2* rhs){
        return rhs->m_timestamp < lhs->m_timestamp;
    });

    emit ui_current_party_idChanged();
    emit ui_drinksChanged();
    emit ui_current_party_startedChanged();
    setDrinksCount(m_drinks.count());
}

void PartyController::endParty()
{
    m_drinks.clear();
    emit ui_drinksChanged();
    setDrinksCount(0);
}

void PartyController::setDrinksCount(int count)
{
    qDebug() << "CURRENT COUnT " << count;
    m_current_drinks_count = count;

    emit ui_drinks_countChanged(m_current_drinks_count);
}

void PartyController::addDrink(const QVariant toast_id, QVariantList involved_users)
{
    qDebug() << "Latest party id " << m_currentPartyId;

    auto newDrink = new drinq::models::Drink2{this};
    newDrink->setPartyId(m_currentPartyId);
    newDrink->setDrinkTypeId(m_drinkController->m_currentDrinkTypeId);
    newDrink->setAmountMl(m_drinkController->m_currentDrinkAmountMl);
    newDrink->setToastId(toast_id);

    if(m_db->create(*newDrink))
    {
        m_drinks.append(newDrink);
        std::sort(m_drinks.begin(), m_drinks.end(), [](drinq::models::Drink2* lhs, drinq::models::Drink2* rhs){
            return rhs->m_timestamp < lhs->m_timestamp;
        });

        for(const auto& u : involved_users)
        {
            const auto sql = QString("INSERT INTO drink_user_rel (drink_id, user_id) VALUES (%1, %2);")
                                .arg(newDrink->m_id.toInt()).arg(u.toInt());
            bool ok = false;
            m_db->execQuery(sql, ok);
        }

        emit ui_drinksChanged();
        setDrinksCount(m_current_drinks_count + 1);
        qDebug() << "PartyController -> drink added";
    }
    else
    {
        qDebug() << "PartyController -> drink not added !";
    }
}

void PartyController::deleteDrink(const QVariant &id)
{
    const auto it = std::find_if(m_drinks.cbegin(), m_drinks.cend(), [id](drinq::models::Drink2* d){
        return d->m_id == id;
    });

    if(it == m_drinks.cend())
    {
        qDebug() << "Unable to find and remove drink with id " << id;
        return;
    }

    auto* drink_ptr = *it;

    qDebug() << "Sanity check drink ptr id " << drink_ptr->m_id;
    qDebug() << "Sanity check last dirnk id " << m_drinks.back()->m_id;

    if(m_db->remove(*drink_ptr))
    {
        m_drinks.removeAll(drink_ptr);
        emit ui_drinksChanged();
        setDrinksCount(m_current_drinks_count - 1);
    }
}
