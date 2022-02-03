#include "partycontroller.h"

#include "databasecontrollerinterface.h"

#include "controllers/drinkcontroller.h"
#include "models/drink.h"

#include <QDebug>

PartyController::PartyController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db, drinq::controllers::DrinkController *drinksController)
    : QObject(parent), m_db(db), m_drinkController(drinksController)
{
}

PartyController::~PartyController()
{
}

QQmlListProperty<drinq::models::Drink2> PartyController::ui_drinks()
{
     return QQmlListProperty<drinq::models::Drink2>(this, m_drinks);
}

void PartyController::startParty()
{
    m_drinks.clear();
    emit ui_drinksChanged();
    setDrinksCount(0);
}

void PartyController::setPartyId(QVariant id)
{
    m_currentPartyId = id;
    auto drinks = m_db->getAll(drinq::models::Drink2{this}, "WHERE party_id = " + m_currentPartyId.toString());

    qDebug() << "Found " << drinks.size() << " drinks";

    for(const auto& d : drinks)
    {
        m_drinks.append(new drinq::models::Drink2(d.toJson(), this));
    }
     setDrinksCount(drinks.count());
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

void PartyController::addDrink()
{
    qDebug() << "Latest party id " << m_currentPartyId;

    auto newDrink = new drinq::models::Drink2{this};
    newDrink->setPartyId(m_currentPartyId);
    newDrink->setDrinkTypeId(m_drinkController->m_currentDrinkTypeIndex);
    newDrink->setAmountMl(m_drinkController->m_currentDrinkAmountMl);

    if(m_db->create(*newDrink))
    {
        m_drinks.append(newDrink);
        std::sort(m_drinks.begin(), m_drinks.end(), [](drinq::models::Drink2* lhs, drinq::models::Drink2* rhs){
            return rhs->m_timestamp < lhs->m_timestamp;
        });

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
