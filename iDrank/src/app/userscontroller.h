#pragma once 

#include <iostream>

#include <optional>
#include <QObject>

#include "user.h"

class UsersController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ui_user_missing READ isUserMissing NOTIFY ui_user_missing_changed)
    
public:
    explicit UsersController(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~UsersController() override {}

public slots:

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
    }

signals:
    void ui_user_missing_changed();

private:
    QMap<int, QString> m_users_map;
};