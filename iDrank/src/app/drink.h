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

    static QList<Drink*> getDrinksForParty(QVariant party_id) 
    {
        QList<Drink*> drinks;

        QSqlQuery query;
        query.prepare("SELECT * FROM drink");

        if(!query.exec())
            qWarning() << "MainWindow::OnSearchClicked - ERROR: " << query.lastError().text();

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