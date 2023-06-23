#pragma once 

#include <optional>
#include <QObject>
#include <QDebug>

#include <iostream>

// Consider using one of the following alternatives to plain SQL queries:
// https://github.com/dpurgin/qtorm
// https://github.com/mrts/datamapper-cpp
// https://github.com/fnc12/sqlite_orm

class Drink : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDateTime ui_timestamp MEMBER m_timestamp CONSTANT)
    Q_PROPERTY(unsigned int ui_amount_ml MEMBER m_amount_ml CONSTANT)
    Q_PROPERTY(QVariant ui_id MEMBER m_id CONSTANT)
    Q_PROPERTY(QVariant ui_drink_type_id MEMBER m_drink_type_id CONSTANT)
    Q_PROPERTY(QVariantList ui_user_ids MEMBER m_user_ids CONSTANT)

public:
    explicit Drink(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Drink() override {}

    void setDrinkTypeId(const QVariant& id) { m_drink_type_id = id; }
    void setPartyId(const QVariant& id) { m_party_id = id;}
    void setAmountMl(unsigned int a) { m_amount_ml = a;}
    void setTimestamp(const QDateTime& ts) { m_timestamp = ts;}
    void setToastId(const QVariant& id) { m_toast_id = id;}

    static std::optional<qint64> secondsSinceLastDrink()
    {
        QSqlQuery query;
        query.prepare("SELECT COUNT(id), MAX(timestamp) FROM drink");

        if(!query.exec())
        {
            qWarning() << "Drink::secondsSinceLastDrink - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        if(query.first() && query.value(0).toInt() > 0)
        {
            const qint64 diff_sec = query.value(1).toDateTime().secsTo(QDateTime::currentDateTime());
            return diff_sec;
        }
        else
        {
            qWarning() << "Drink::secondsSinceLastDrink - last drink not found";
            return {};
        }
    }

    static QList<Drink*> getDrinksForParty(QVariant party_id) 
    {
        QList<Drink*> drinks;

        QSqlQuery query;
        query.prepare("SELECT drink.id, drink.timestamp, drink.amount_ml, drink.toast_id, GROUP_CONCAT(user_drink.user_id) FROM drink "
                      "LEFT JOIN user_drink ON drink.id = user_drink.drink_id "
                      "WHERE party_id = :party_id GROUP BY drink.id");
        query.bindValue(":party_id", party_id);

        if(!query.exec())
        {
            qWarning() << "Drink::getDrinksForParty - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
        }

        while(query.next())
        {
            auto* d = new Drink;
            d->m_id = query.value(0);
            d->m_timestamp = query.value(1).toDateTime();
            d->m_amount_ml = query.value(2).toInt();
            d->m_party_id = party_id;
            d->m_toast_id = query.value(3);

            QVariantList user_ids;
            for(const auto& id : query.value(4).toString().split(','))
            {
                user_ids.append(id.toInt());
            }

            d->m_user_ids = user_ids;
            drinks.append(d);
        }

        return drinks;
    }

    static QList<Drink*> getDrinksForUserInParty(QVariant user_id, QVariant party_id) 
    {
        QList<Drink*> drinks;

        QSqlQuery query;
        query.prepare("SELECT drink.id, drink.timestamp, drink.amount_ml, drink.toast_id FROM drink "
                      "LEFT JOIN user_drink ON drink.id = user_drink.drink_id "
                      "WHERE drink.party_id = :party_id AND user_drink.user_id = :user_id");
        query.bindValue(":party_id", party_id);
        query.bindValue(":user_id", user_id);

        if(!query.exec())
        {
            qWarning() << "Drink::getDrinksForUserInParty - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
        }

        while(query.next())
        {
            auto* d = new Drink;
            d->m_id = query.value(0);
            d->m_timestamp = query.value(1).toDateTime();
            d->m_amount_ml = query.value(2).toInt();
            d->m_party_id = party_id;
            d->m_toast_id = query.value(3);
            QVariantList user_ids {user_id};
            d->m_user_ids = user_ids;
            drinks.append(d);
        }

        return drinks;
    }

    static std::optional<QVariant> add(QVariant drink_type_id, QVariant party_id, QDateTime timestamp, int amount_ml, QVariant toast_id)
    {
        QSqlQuery query;
        query.prepare(QString("INSERT INTO drink (drink_type_id, party_id, timestamp, amount_ml, toast_id)"
                              " VALUES (:drink_type_id, :party_id, :timestamp, :amount_ml, :toast_id)"));

        query.bindValue(":drink_type_id", drink_type_id);
        query.bindValue(":party_id", party_id);
        query.bindValue(":timestamp", timestamp);
        query.bindValue(":amount_ml", amount_ml);
        query.bindValue(":toast_id", toast_id);

        if(!query.exec())
        {
            qWarning() << "Drink::add - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        const auto drink_id = query.lastInsertId();
        return drink_id;
    }

    static bool remove(QVariant drink_id)
    {
        QSqlQuery query;
        query.prepare(QString("DELETE FROM drink WHERE id = :id"));
        query.bindValue(":id", drink_id);

        if(!query.exec())
        {
            qWarning() << "Drink::remove - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return false;
        }

        return true;
    }

public:
    QVariant m_id; //replace with base class like DatabaseObject
    QVariant m_drink_type_id{};
    QVariant m_party_id{};
    QDateTime m_timestamp{};
    unsigned int m_amount_ml{0};
    QVariant m_toast_id{};
    QVariantList m_user_ids{};
};