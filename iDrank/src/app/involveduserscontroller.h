#pragma once 

#include <iostream>

#include <optional>
#include <QObject>

const QString INVOLVED_USERS_KEY = "involved_users";

class InvolvedUsersController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList ui_involved_users MEMBER m_involved_users NOTIFY ui_involved_users_changed)
    
public:
    explicit InvolvedUsersController(QSettings& settings, QObject* parent = nullptr) 
        : QObject(parent) 
        , m_settings(settings)
    {
        if(m_settings.contains(INVOLVED_USERS_KEY))
        {
            m_involved_users = m_settings.value(INVOLVED_USERS_KEY).toString().split(',', Qt::SkipEmptyParts);
            emit ui_involved_users_changed();
        }

        qDebug() << "Involved users " << m_involved_users.size();
    }

    virtual ~InvolvedUsersController() override 
    {
        m_settings.setValue(INVOLVED_USERS_KEY, m_involved_users.join(','));
    }

public slots:
    void setInvolvedUser(const QString& user_id, bool involved)
    {
        if(involved)
        {
            m_involved_users.append(user_id);
        }
        else
        {
            m_involved_users.removeAll(user_id);
        }

        emit ui_involved_users_changed();
    }

signals:
    void ui_involved_users_changed();

private:
    QSettings& m_settings;
    QStringList m_involved_users;
};