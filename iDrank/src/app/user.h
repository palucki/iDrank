#pragma once 

#include <optional>
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant ui_id MEMBER m_id CONSTANT)
    Q_PROPERTY(QString ui_name MEMBER m_name CONSTANT)
    Q_PROPERTY(bool ui_involved MEMBER m_involved WRITE setInvolved NOTIFY ui_involved_changed)
    
public:
    explicit User(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~User() override {}

    void setInvolved(bool involved)
    {
        m_involved = involved;
        emit ui_involved_changed();
    }

    static QList<User*> getUsersForParty(QVariant party_id)
    {
        qDebug() << "Getting users for party " << party_id;

        QList<User*> users;

        QSqlQuery query;
        query.prepare("SELECT DISTINCT user.id, user.name, user.admin "
                      "FROM user_drink "
                      "LEFT JOIN drink ON drink.id = drink_id "
                      "LEFT JOIN user ON user.id = user_id "
                      "WHERE drink.party_id = :party_id AND user.id IS NOT NULL");
        query.bindValue(":party_id", party_id);

        if(!query.exec())
        {
            qWarning() << "User::getUsersForParty - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        while(query.next())
        {
            auto* ud = new User;
            ud->m_id = query.value(0);
            ud->m_name = query.value(1).toString();
            ud->m_admin = query.value(2).toInt() > 0;
            users.append(ud);
        }

        return users;
    }

    static QList<User*> getUsers() 
    {
        QList<User*> users;

        QSqlQuery query;
        query.prepare("SELECT id, name, admin FROM user");

        if(!query.exec())
        {
            qWarning() << "User::getUsers - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        while(query.next())
        {
            auto* ud = new User;
            ud->m_id = query.value(0);
            ud->m_name = query.value(1).toString();
            ud->m_admin = query.value(2).toInt() > 0;
            users.append(ud);
        }

        return users;
    }

    static std::optional<QVariant> add(const QString& name, bool admin)
    {
        QSqlQuery query;
        query.prepare(QString("INSERT INTO user (name, admin)"
                              " VALUES (:name, :admin)"));

        query.bindValue(":name", name);
        query.bindValue(":admin", admin ? 1 : 0);

        if(!query.exec())
        {
            qWarning() << "User::add - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        const auto user_id = query.lastInsertId();
        return user_id;
    }

    static bool remove(const QVariant& user_id)
    {
        QSqlQuery query;
        query.prepare(QString("DELETE FROM user WHERE id = :id"));
        query.bindValue(":id", user_id);

        if(!query.exec())
        {
            qWarning() << "User::remove - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return false;
        }

        return true;
    }

signals:
    void ui_involved_changed();

public:
    QVariant m_id; //replace with base class like DatabaseObject
    QString m_name;
    bool m_admin;
    bool m_involved{false};
};