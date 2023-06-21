#pragma once 

#include <optional>
#include <QObject>

#include "user.h"

class UsersController : public QObject
{
    Q_OBJECT
    
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
private:
    QMap<int, QString> m_users_map;
};