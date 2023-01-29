#pragma once

#include <memory>
#include <QObject>
#include <QVariant>
#include <drinq-lib_global.h>

#include "models/drink.h"
#include "framework/drinkprovider.h"

namespace drinq::controllers {
class DatabaseControllerInterface;
class DrinkController;
}

namespace drinq::models {
class Party2;
}
//plotting

#include <QtCharts/QAbstractSeries>
QT_CHARTS_USE_NAMESPACE

class DRINQLIB_EXPORT PartyController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ui_drinks_count MEMBER m_current_drinks_count NOTIFY ui_drinks_countChanged)
    Q_PROPERTY(QVariant ui_current_party_id MEMBER m_currentPartyId NOTIFY ui_current_party_idChanged)
    Q_PROPERTY(QDateTime ui_current_party_started MEMBER m_currentPartyStarted NOTIFY ui_current_party_startedChanged)

public:
    explicit PartyController(QObject *parent = nullptr,
                             drinq::controllers::DatabaseControllerInterface* db = nullptr,
                             drinq::controllers::DrinkController* drinksController = nullptr);
    virtual ~PartyController();

public slots:

    qint64 secondsSinceLastDrink();

    void startParty();
    void setPartyId(QVariant id);
    void endParty();

    void addDrink(const QVariant toast_id, QVariantList involved_users);
    void deleteDrink(const QVariant& id);

signals:
    void ui_drinks_countChanged(int count);
    void ui_drinksChanged();
    void ui_current_party_idChanged();
    void ui_current_party_startedChanged();

private:
    void setDrinksCount(int count);

    drinq::controllers::DatabaseControllerInterface* m_db = nullptr;
    drinq::controllers::DrinkController* m_drinkController = nullptr;

    DrinkProvider m_drinkProvider;

    //PartyController to tylko malutka klasa posiadajaca start i end party
    //cala reszta to bedzie Drinks Proviider albo cos w tym stylu
    QList<drinq::models::Drink2*> m_drinks;
    int m_current_drinks_count = 0;
    QVariant m_currentPartyId;
    QDateTime m_currentPartyStarted;
    unsigned int m_current_sum = 0;

};
