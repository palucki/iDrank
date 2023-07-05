#pragma once 

#include <optional>
#include <QObject>

#include "user.h"
#include "party.h"
#include "drink.h"
#include "userdrink.h"

class PartyController : public QObject
{
    Q_PROPERTY(bool ui_party_started READ isPartyStarted NOTIFY ui_party_started_changed)
    Q_PROPERTY(int ui_drinks_count MEMBER m_current_drinks_count NOTIFY ui_drinks_count_changed)
    Q_PROPERTY(QString ui_party_title READ currentPartyTitle NOTIFY ui_party_title_changed)
    Q_PROPERTY(QList<Party*> ui_parties READ getParties NOTIFY ui_parties_changed)
    Q_PROPERTY(int ui_party_id MEMBER m_current_party_id NOTIFY ui_party_id_changed)

    Q_OBJECT
    
public:
    explicit PartyController(QObject* parent = nullptr) : QObject(parent) 
    {
        auto party_data = Party::getCurrentParty();
        m_current_party_title = party_data.second;
        m_current_party_id = party_data.first;

        auto drinks = Drink::getDrinksForParty(m_current_party_id);
        m_current_drinks_count = drinks.size();

        emit ui_party_title_changed();
        emit ui_drinks_count_changed();
        emit ui_party_id_changed();
    }
    virtual ~PartyController() override {}

public slots:
    QList<User*> getUsersForParty(const QVariant& party_id)
    {
        Q_UNUSED(party_id);
        return User::getUsers();
    }

    QList<Party*> getParties()
    {
        return Party::getAll();
    }

    bool isPartyStarted()
    {
        return Party::isAnyStarted();
    }

    QString currentPartyTitle()
    {
        if(m_current_party_title.isEmpty())
        {
            auto party_data = Party::getCurrentParty();
            m_current_party_title = party_data.second;
            m_current_party_id = party_data.first;
        }

        return m_current_party_title;
    }

    qint64 secondsSinceLastDrink()
    {
        const auto seconds_since_last_drink = Drink::secondsSinceLastDrink();
        if (seconds_since_last_drink)
            return *seconds_since_last_drink;

        return 0;
    }

    void startParty(const QString& name)
    {
        const auto party_id = Party::start(name);
        if(!party_id)
        {
            std::cout << "ERROR: unable to start party\n";
            return;
        }

        m_current_party_title = name;
        m_current_party_id = (*party_id).toInt();
        m_current_drinks_count = 0;

        emit ui_party_started_changed();
        emit ui_party_title_changed();
        emit ui_drinks_count_changed();
        emit ui_party_id_changed();
    }

    void endParty()
    {
        if(!Party::end())
        {
            std::cout << "ERROR: unable to end party\n";
            return;
        }
        emit ui_party_started_changed();
    }

    void addDrink(QVariant toast_id, QVariant drink_type_id, int amount_ml, QStringList involved_users)
    {
        auto drink_id = Drink::add(drink_type_id, m_current_party_id, QDateTime::currentDateTime(), amount_ml, toast_id);
        if(!drink_id)
        {
            qDebug() << "ERROR unable to add drink";
        }
        
        for(auto user : involved_users)
        {
            if(!UserDrink::add(user.trimmed(), *drink_id))
            {
                qDebug() << "ERROR unable to add user-drink";
            }
        }

        m_current_drinks_count++;
        emit ui_drinks_count_changed();
    }

signals:
    void ui_party_started_changed();
    void ui_drinks_count_changed();
    void ui_party_title_changed();
    void ui_parties_changed();
    void ui_party_id_changed();

private: 
    int m_current_drinks_count{0};
    int m_current_party_id;
    QString m_current_party_title;
};