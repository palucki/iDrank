#pragma once 

#include <QObject>

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

public:
    explicit Drink(QObject* parent = nullptr) {}
    virtual ~Drink() {}

    void setDrinkTypeId(const QVariant& id) { m_drink_type_id = id; }
    void setPartyId(const QVariant& id) { m_party_id = id;}
    void setAmountMl(unsigned int a) { m_amount_ml = a;}
    void setTimestamp(const QDateTime& ts) { m_timestamp = ts;}
    void setToastId(const QVariant& id) { m_toast_id = id;}

    static qint64 secondsSinceLastDrink()
    {
        QSqlQuery query;
        query.prepare("SELECT COUNT(id), MAX(timestamp) FROM drink");

        if(!query.exec())
        {
            qWarning() << "Drink::secondsSinceLastDrink - ERROR: " << query.lastError().text();
            return -1;
        }

        if(query.first() && query.value(0).toInt() > 0)
        {
            const qint64 diff_sec = query.value(1).toDateTime().secsTo(QDateTime::currentDateTime());
            return diff_sec;
        }
        else
        {
            qWarning() << "Drink::secondsSinceLastDrink - last drink not found";
            return -1;
        }
    }

    static QList<Drink*> getDrinksForParty(QVariant party_id) 
    {
        QList<Drink*> drinks;

        QSqlQuery query;
        query.prepare("SELECT * FROM drink WHERE party_id = :party_id");
        query.bindValue(":party_id", party_id);

        if(!query.exec())
        {
            qWarning() << "Drink::getDrinksForParty - ERROR: " << query.lastError().text();
        }

        while(query.next())
        {
            drinks.append(new Drink{});
        }

        return drinks;
    }

public:
    QVariant m_id; //replace with base class like DatabaseObject
    QVariant m_drink_type_id{};
    QVariant m_party_id{};
    QDateTime m_timestamp{};
    unsigned int m_amount_ml{0};
    QVariant m_toast_id{};
};