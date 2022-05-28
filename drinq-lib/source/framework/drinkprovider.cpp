#include "drinkprovider.h"
#include "controllers/databasecontrollerinterface.h"

DrinkProvider::DrinkProvider(drinq::controllers::DatabaseControllerInterface *db)
    : m_db(db)
{

}

QVariantList/*QQmlListProperty<drinq::models::Drink2>*/ DrinkProvider::getUIDrinksList(QVariant partyId)
{
    QVariantList result;
    auto drinks = m_db->getAll(drinq::models::Drink2{this}, "WHERE party_id = " + partyId.toString());

    qDebug() << "Found " << drinks.size() << " drinks in drink provider";

//    std::sort(drinks.begin(), drinks.end(), [](drinq::data::EntityLite& lhs, drinq::data::EntityLite& rhs){
//        qDebug() << "LHS " << lhs.m_data["timestamp"].toDateTime();
//        qDebug() << "RHS " << rhs.m_data["timestamp"].toDateTime();
//        return rhs.m_data["timestamp"].toDateTime() < lhs.m_data["timestamp"].toDateTime();
//    });

    for(auto d : drinks)
    {
//        drinq::models::Drink2 drink(d.toJson(), this);
        result.append(QVariant::fromValue(new drinq::models::Drink2(d.toJson(), this)));
//        m_drinks.append(new drinq::models::Drink2(d.toJson(), this));
    }

//    std::sort(result.begin(), result.end(), [](const QVariant& lhs, const QVariant& rhs){
//        QObject *object = qvariant_cast<QObject*>(&lhs);
//        drinq::models::Drink2* lhs_drink = qobject_cast<drinq::models::Drink2*>(object);
//        object = qvariant_cast<QObject*>(&rhs);
//        drinq::models::Drink2* rhs_drink = qobject_cast<drinq::models::Drink2*>(object);

//        return rhs_drink->m_timestamp < lhs_drink->m_timestamp;
//    });

//    std::reverse(result.begin(), result.end());

    return result; /*QQmlListProperty<drinq::models::Drink2>(this, &m_drinks);*/
}

QList<drinq::models::Drink2 *> DrinkProvider::getDrinksList(QVariant partyId)
{
    auto drinks = m_db->getAll(drinq::models::Drink2{this}, "WHERE party_id = " + partyId.toString());

    qDebug() << "Found " << drinks.size() << " drinks in drink provider";

    QList<drinq::models::Drink2*> result;
    for(auto d : drinks)
    {
//        drinq::models::Drink2 drink(d.toJson(), this);
//        result.append(QVariant::fromValue(new drinq::models::Drink2(d.toJson(), this)));
//        m_drinks.append(new drinq::models::Drink2(d.toJson(), this));
        result.append(new drinq::models::Drink2(d.toJson(), this));
    }

    return result;
}

//void DrinkProvider::update(QAbstractSeries* series)
//{
//    Q_UNUSED(series);
//}
