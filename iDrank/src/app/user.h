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
    
public:
    explicit User(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~User() override {}

    static QList<User*> getUsers() 
    {
        QList<User*> users;

        QSqlQuery query;
        query.prepare("SELECT id, name FROM user");

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
            users.append(ud);
        }

        return users;
    }

    static std::optional<QVariant> add(const QString& name)
    {
        QSqlQuery query;
        query.prepare(QString("INSERT INTO user (name)"
                              " VALUES (:name)"));

        query.bindValue(":name", name);

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

public:
    QVariant m_id; //replace with base class like DatabaseObject
    QString m_name;
};