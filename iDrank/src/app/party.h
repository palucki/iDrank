#pragma once 

#include <optional>

#include <QObject>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

class Party : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant ui_id MEMBER m_id CONSTANT)
    Q_PROPERTY(QString ui_name MEMBER m_name CONSTANT)
    Q_PROPERTY(QDateTime ui_started MEMBER m_started CONSTANT)
    Q_PROPERTY(QDateTime ui_ended MEMBER m_ended CONSTANT)

public:
    explicit Party(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Party() override {}

    void setName(const QString& name) { m_name = name; }
    void setStarted(const QDateTime& ts) { m_started = ts;}
    void setEnded(const QDateTime& ts) { m_ended = ts;}

    static QVariantList usersInParty(QVariant party_id)
    {
        QSqlQuery query;
        query.prepare(QString("SELECT DISTINCT(user_drink.user_id) FROM drink "
                              "LEFT JOIN user_drink ON drink.id = user_drink.drink_id "
                              "WHERE drink.party_id = :party_id"));

        query.bindValue(":party_id", party_id);

        if(!query.exec())
        {
            qWarning() << "Party::usersInParty - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        QVariantList user_ids;
        while(query.next())
        {
            user_ids.append(query.value(0));
        }

        return user_ids;
    }

    static QPair<int, QString> getCurrentParty()
    {
        QSqlQuery query;
        query.prepare("SELECT id, name FROM party WHERE started IS NOT NULL AND ended IS NULL ORDER BY id DESC");

        if(!query.exec())
        {
            qWarning() << "Party::getCurrentParty - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        if(query.first())
        {
            return {query.value(0).toInt(), query.value(1).toString()};
        }

        return {};
    }

    static bool isAnyStarted()
    {
        QSqlQuery query;
        query.prepare("SELECT COUNT(id) FROM party WHERE started IS NOT NULL AND ended IS NULL");

        if(!query.exec())
        {
            qWarning() << "Party::isAnyStarted - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        if(query.first() && query.value(0).toInt() > 0)
        {
            return true;
        }

        return false;
    }

    static std::optional<QVariant> start(const QString& name)
    {
        return Party::add(name, QDateTime::currentDateTime());
    }

    static bool end()
    {
        QSqlQuery query;
        query.prepare(QString("UPDATE party SET ended = :ended WHERE ended IS NULL"));
        query.bindValue(":ended", QDateTime::currentDateTime());

        if(!query.exec())
        {
            qWarning() << "Party::remove - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return false;
        }

        return true;
    }

    static std::optional<QVariant> add(QString name, QDateTime started)
    {
        QSqlQuery query;
        query.prepare(QString("INSERT INTO party (name, started)"
                              " VALUES (:name, :started)"));

        query.bindValue(":name", name);
        query.bindValue(":started", started);

        if(!query.exec())
        {
            qWarning() << "Party::add - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        const auto party_id = query.lastInsertId();
        return party_id;
    }

    static bool remove(QVariant party_id)
    {
        QSqlQuery query;
        query.prepare(QString("DELETE FROM party WHERE id = :id"));
        query.bindValue(":id", party_id);

        if(!query.exec())
        {
            qWarning() << "Party::remove - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return false;
        }

        return true;
    }

    static QList<Party*> getAll()
    {
        QList<Party*> parties;

        QSqlQuery query;
        query.prepare("SELECT id, name, started, ended FROM party");

        if(!query.exec())
        {
            qWarning() << "DrinkType::getDrinkTypes - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        while(query.next())
        {
            auto* p = new Party;
            p->m_id = query.value(0);
            p->m_name = query.value(1).toString();
            p->m_started = query.value(2).toDateTime();
            p->m_ended = query.value(3).toDateTime();
            parties.append(p);
        }

        return parties;
    }

public:
    QVariant m_id; //replace with base class like DatabaseObject
    QString m_name{};
    QDateTime m_started{};
    QDateTime m_ended{};
};