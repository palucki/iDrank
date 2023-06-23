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

    bool isPartyStarted()
    {
        return Party::isAnyStarted();
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
        }

        ui_party_started_changed();
    }


signals:
    void ui_party_started_changed();
    void ui_drinks_count_changed();

private: 
    int m_current_drinks_count;
};