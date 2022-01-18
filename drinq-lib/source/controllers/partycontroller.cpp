#include "partycontroller.h"

#include "databasecontrollerinterface.h"

#include "controllers/drinkcontroller.h"
#include "models/drink.h"

#include <QDebug>

PartyController::PartyController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db, drinq::controllers::DrinkController *drinksController)
    : QObject(parent), m_db(db), m_drinkController(drinksController)
{
    auto lastId = m_db->getLastId("party");

    m_current_party = std::make_unique<drinq::models::Party2>();
    m_current_party->setId(lastId);
    m_db->get(*m_current_party);

    //fix to keep state up to date
//    m_current_party->update();

    qDebug() << "Latest party " << m_current_party->toJson();

    if(isPartyStarted())
    {
        m_party_started = true;
        auto drinks = m_db->getAll(drinq::models::Drink2{this}, "WHERE party_id = " + lastId.toString());

        qDebug() << "Found " << drinks.size() << " drinks";

        for(const auto& d : drinks)
        {
    //        qDebug() << drink_type.m_name << " default amount: " << drink_type.m_default_amount_ml;
            m_drinks.append(new drinq::models::Drink2(d.toJson(), this));
        }

        setDrinksCount(drinks.count());
    }

    qDebug() << "drinks count: " << m_current_drinks_count;
}

PartyController::~PartyController()
{
}

QQmlListProperty<drinq::models::Drink2> PartyController::ui_drinks()
{
     return QQmlListProperty<drinq::models::Drink2>(this, m_drinks);
}

bool PartyController::isPartyStarted()
{
//    return m_party_started;
    return m_current_party->m_data["ended"].toDateTime().isNull();
//TODO: fix after propoer update() methods are added for all classes deriving from enetity
//    return m_current_party->m_ended.isNull();
}

void PartyController::startParty()
{
    m_drinks.clear();
    emit ui_drinksChanged();

    m_current_party = std::make_unique<drinq::models::Party2>();
    setDrinksCount(0);
    m_db->create(*m_current_party);

    m_party_started = isPartyStarted();
    emit ui_party_startedChanged();
}

void PartyController::endParty()
{
    m_drinks.clear();
    emit ui_drinksChanged();

    m_current_party->setEnded(QDateTime::currentDateTime());
    setDrinksCount(0);
    m_db->update(*m_current_party);

    m_party_started = isPartyStarted();
    emit ui_party_startedChanged();
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

void PartyController::addDrink()
{
    qDebug() << "Latest party id " << currentPartyId();

    auto newDrink = new drinq::models::Drink2{this};
    newDrink->setPartyId(currentPartyId());
    newDrink->setDrinkTypeId(m_drinkController->m_currentDrinkTypeIndex);
    newDrink->setAmountMl(m_drinkController->m_currentDrinkAmountMl);

    qDebug() << "Adding drink: " << newDrink->toJson();
    qDebug() << "Result " << m_db->create(*newDrink);
    qDebug() << "PartyController -> drink added";
    m_drinks.append(newDrink);

    emit ui_drinksChanged();

    setDrinksCount(m_current_drinks_count + 1);
}
