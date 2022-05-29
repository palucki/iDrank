#include "drinkprovider.h"
#include "controllers/databasecontrollerinterface.h"

DrinkProvider::DrinkProvider(drinq::controllers::DatabaseControllerInterface *db)
    : m_db(db)
{
}

QVariantList DrinkProvider::getUIDrinksList(QVariant partyId)
{
    QVariantList result;
    auto drinks = m_db->getAll(drinq::models::Drink2{this}, "WHERE party_id = " + partyId.toString());

    qDebug() << "Found " << drinks.size() << " drinks in drink provider";

    for(auto d : drinks)
    {
        result.append(QVariant::fromValue(new drinq::models::Drink2(d.toJson(), this)));
    }

    return result;
}

QList<drinq::models::Drink2 *> DrinkProvider::getDrinksList(QVariant partyId)
{
    auto drinks = m_db->getAll(drinq::models::Drink2{this}, "WHERE party_id = " + partyId.toString());

    qDebug() << "Found " << drinks.size() << " drinks in drink provider";

    QList<drinq::models::Drink2*> result;
    for(auto& d : drinks)
    {
        result.append(new drinq::models::Drink2(d.toJson(), this));
    }

    return result;
}
