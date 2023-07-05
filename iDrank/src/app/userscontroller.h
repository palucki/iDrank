#pragma once 

#include <iostream>

#include <optional>
#include <QObject>

#include "user.h"

class UsersController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ui_user_missing READ isUserMissing NOTIFY ui_user_missing_changed)
    Q_PROPERTY(QString ui_admin_name MEMBER m_admin_name NOTIFY ui_admin_name_changed)
    
public:
    explicit UsersController(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~UsersController() override {}

public slots:

    QList<User*> getUsers(bool force_fetch = false)
    {
        if(m_users.isEmpty() || force_fetch)
        {
            m_users = User::getUsers();
        }

        return m_users;
    }

    QMap<int, QString> getUsersNameMap()
    {
        if(!m_users_map.isEmpty())
        {
            return m_users_map;
        }

        const auto users = User::getUsers();
        
        QMap<int, QString> users_map;
        for(auto u : users)
        {
            users_map[u->m_id.toInt()] = u->m_name;
            
            if(u->m_admin)
            {
                m_admin_name = u->m_name;
                emit ui_admin_name_changed();
            }
        }

        m_users_map = users_map;
        return m_users_map;
    }

    bool isUserMissing()
    {
        return getUsersNameMap().isEmpty();
    }

    void registerUser(const QString& name)
    {
        if(name.isEmpty())
        {
            std::cout << "ERROR - empty user name\n";
            return;
        }

        const bool is_admin = isUserMissing();

        if(User::add(name, is_admin))
        {
            emit ui_user_missing_changed();
        }

        if(is_admin)
        {
            m_admin_name = name;
            emit ui_admin_name_changed();
        }
    }

    void deleteUser(QVariant id)
    {
        User::remove(id);
    }

signals:
    void ui_user_missing_changed();
    void ui_admin_name_changed();

private:
    QList<User*> m_users;
    QMap<int, QString> m_users_map;
    QString m_admin_name;
};