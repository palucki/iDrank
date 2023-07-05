#pragma once 

#include <iostream>

#include <optional>
#include <QObject>
#include <QSettings>

#include "user.h"

const QString INVOLVED_USERS_KEY = "involved_users";

class UsersController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ui_user_missing READ isUserMissing NOTIFY ui_user_missing_changed)
    Q_PROPERTY(QString ui_admin_name MEMBER m_admin_name NOTIFY ui_admin_name_changed)
    Q_PROPERTY(QStringList ui_involved_users MEMBER m_involved_users NOTIFY ui_involved_users_changed)
    
public:
    explicit UsersController(QSettings& settings, QObject* parent = nullptr) 
        : QObject(parent) 
        , m_settings(settings)
    {
        if(m_settings.contains(INVOLVED_USERS_KEY))
        {
            m_involved_users = m_settings.value(INVOLVED_USERS_KEY).toString().split(',', Qt::SkipEmptyParts);
            qDebug() << "Involved users " << m_involved_users.size();
            emit ui_involved_users_changed();
        }
    }

    virtual ~UsersController() override {}

public slots:

    QList<User*> getUsers(bool force_fetch = false)
    {
        if(m_users.isEmpty() || force_fetch)
        {
            m_users = User::getUsers();
        }

        if(m_settings.contains(INVOLVED_USERS_KEY))
        {
            m_involved_users = m_settings.value(INVOLVED_USERS_KEY).toString().split(',', Qt::SkipEmptyParts);
            qDebug() << "Involved users " << m_involved_users.size();

            for(auto* user : m_users)
            {
                if(m_involved_users.contains(user->m_id.toString()))
                {
                    user->setInvolved(true);
                }
            }

            emit ui_involved_users_changed();
        }

        return m_users;
    }

    QMap<int, QString> getUsersNameMap(bool force_fetch = false)
    {
        if(!m_users_map.isEmpty() && !force_fetch)
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

        emit users_changed();
    }

    void deleteUser(QVariant id)
    {
        User::remove(id);

        emit users_changed();
    }

    void setInvolvedUsers(const QVariantList& users)
    {
        m_involved_users.clear();
        for(const auto& u : users)
        {
            m_involved_users.append(QString::number(u.toInt()));
        }
        m_settings.setValue(INVOLVED_USERS_KEY, m_involved_users.join(','));
        qDebug() << "Setting involved to " << m_involved_users;
        emit ui_involved_users_changed();
    }

signals:
    void ui_user_missing_changed();
    void ui_admin_name_changed();
    void ui_involved_users_changed();
    void users_changed();

private:
    QList<User*> m_users;
    QMap<int, QString> m_users_map;
    QString m_admin_name;

    QSettings& m_settings;
    QStringList m_involved_users;
};