#pragma once

#include <memory>
#include <QObject>
#include <QVariant>
#include <drinq-lib_global.h>

#include "models/drink.h"

namespace drinq::controllers {
class DatabaseControllerInterface;
class DrinkController;
}

namespace drinq::models {
class Party2;
}

class DRINQLIB_EXPORT PartyController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ui_drinks_count MEMBER m_current_drinks_count NOTIFY ui_drinks_countChanged)
    Q_PROPERTY(QQmlListProperty<drinq::models::Drink2> ui_drinks READ ui_drinks NOTIFY ui_drinksChanged )
    Q_PROPERTY(bool ui_party_started MEMBER m_party_started NOTIFY ui_party_startedChanged)
public:
    explicit PartyController(QObject *parent = nullptr,
                             drinq::controllers::DatabaseControllerInterface* db = nullptr,
                             drinq::controllers::DrinkController* drinksController = nullptr);
    virtual ~PartyController();

    Q_INVOKABLE QQmlListProperty<drinq::models::Drink2> ui_drinks();

public slots:
    void startParty();
    void endParty();
    void setPartyName(const QString& name);
    QVariant currentPartyId();
    void setDrinksCount(int count);

    void addDrink();
    void deleteDrink(const QVariant& id);

signals:
    void ui_drinks_countChanged(int count);
    void ui_drinksChanged();
    void ui_party_startedChanged();

private:
    bool isPartyStarted();

    drinq::controllers::DatabaseControllerInterface* m_db = nullptr;
    drinq::controllers::DrinkController* m_drinkController = nullptr;
    std::unique_ptr<drinq::models::Party2> m_current_party;
    QList<drinq::models::Drink2*> m_drinks;
    int m_current_drinks_count = 0;
    bool m_party_started = false;
};
