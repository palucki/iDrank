#pragma once 

#include <optional>
#include <QObject>

class UserDrink : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant ui_id MEMBER m_id CONSTANT)
    Q_PROPERTY(QVariant ui_user_id MEMBER m_user_id CONSTANT)
    Q_PROPERTY(QVariant ui_drink_id MEMBER m_drink_id CONSTANT)
    
public:
    explicit UserDrink(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~UserDrink() override {}

    void setUserId(const QVariant& user_id) { m_user_id = user_id; }
    void setDrinkId(const QVariant& drink_id) { m_drink_id = drink_id; }
    
    static QList<UserDrink*> getUserDrinks(const QVariant& user_id) 
    {
        QList<UserDrink*> user_drinks;

        QSqlQuery query;
        query.prepare("SELECT id, user_id, drink_id FROM user_drink");

        if(!query.exec())
        {
            qWarning() << "UserDrink::getUserDrinks - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        while(query.next())
        {
            auto* ud = new UserDrink;
            ud->m_id = query.value(0);
            ud->m_user_id = query.value(1);
            ud->m_drink_id = query.value(2);
            user_drinks.append(ud);
        }

        return user_drinks;
    }

    static std::optional<QVariant> add(const QVariant& user_id, const QVariant& drink_id)
    {
        QSqlQuery query;
        query.prepare(QString("INSERT INTO user_drink (user_id, drink_id)"
                              " VALUES (:user_id, :drink_id)"));

        query.bindValue(":user_id", user_id);
        query.bindValue(":drink_id", drink_id);

        if(!query.exec())
        {
            qWarning() << "UserDrink::add - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        const auto user_drink_id = query.lastInsertId();
        return user_drink_id;
    }

    static bool remove(const QVariant& user_drink_id)
    {
        QSqlQuery query;
        query.prepare(QString("DELETE FROM user_drink WHERE id = :id"));
        query.bindValue(":id", user_drink_id);

        if(!query.exec())
        {
            qWarning() << "UserDrink::remove - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return false;
        }

        return true;
    }

public:
    QVariant m_id; //replace with base class like DatabaseObject
    QVariant m_user_id;
    QVariant m_drink_id;
};