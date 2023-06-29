#pragma once 

#include <optional>
#include <QObject>

#include "user.h"
#include "party.h"
#include "drink.h"

class PartyController : public QObject
{
    Q_PROPERTY(bool ui_party_started READ isPartyStarted NOTIFY ui_party_started_changed)
    Q_PROPERTY(int ui_drinks_count MEMBER m_current_drinks_count NOTIFY ui_drinks_count_changed)
    Q_PROPERTY(QString ui_party_title READ currentPartyTitle NOTIFY ui_party_title_changed)
    Q_PROPERTY(QList<Party*> ui_parties READ getParties NOTIFY ui_parties_changed)

    Q_OBJECT
    
public:
    explicit PartyController(QObject* parent = nullptr) : QObject(parent) {}
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
            m_current_party_title = Party::getCurrentPartyTitle();
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
        if(!Party::start(name))
        {
            std::cout << "ERROR: unable to start party\n";
            return;
        }

        m_current_party_title = name;

        ui_party_started_changed();
        ui_party_title_changed();
    }

    void endParty()
    {
        if(!Party::end())
        {
            std::cout << "ERROR: unable to end party\n";
            return;
        }
        ui_party_started_changed();
    }

    void addDrink(int toast_id, QStringList involved_users)
    {
        // add(QVariant drink_type_id, QVariant party_id, QDateTime timestamp, int amount_ml, QVariant toast_id)
        
        // if(!Drink::add(drink_type_id, party_id, QDateTime::currentDateTime(), amount_ml, toast_id))
        // {

        // }

        // for(auto user : involved_users)
        // {

        // }
    }

signals:
    void ui_party_started_changed();
    void ui_drinks_count_changed();
    void ui_party_title_changed();
    void ui_parties_changed();

private: 
    int m_current_drinks_count{0};
    int m_current_party;
    QString m_current_party_title;
};