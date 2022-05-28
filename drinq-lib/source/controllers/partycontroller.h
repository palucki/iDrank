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
//    Q_PROPERTY(qint64 ui_seconds_since_last_drink READ secondsSinceLastDrink NOTIFY ui_secondsChanged)
    Q_PROPERTY(QQmlListProperty<drinq::models::Drink2> ui_drinks READ ui_drinks NOTIFY ui_drinksChanged )

    //for plotting the drinks consumption
    Q_PROPERTY(unsigned int ui_plot_max_value MEMBER m_current_sum NOTIFY ui_plot_max_valueChanged)

    Q_PROPERTY(QVariant ui_current_party_id MEMBER m_currentPartyId NOTIFY ui_current_party_idChanged)

public:
    explicit PartyController(QObject *parent = nullptr,
                             drinq::controllers::DatabaseControllerInterface* db = nullptr,
                             drinq::controllers::DrinkController* drinksController = nullptr);
    virtual ~PartyController();

    Q_INVOKABLE QQmlListProperty<drinq::models::Drink2> ui_drinks();
    Q_INVOKABLE unsigned int ui_plot_max_value();

public slots:

    qint64 secondsSinceLastDrink();

    void startParty();
    void setPartyId(QVariant id);
    void endParty();

    void addDrink();
    void deleteDrink(const QVariant& id);

    //plotting
    void update(QAbstractSeries *series, QAbstractSeries *start);
    QDateTime plot_min();
    QDateTime plot_max();

signals:
    void ui_drinks_countChanged(int count);
    void ui_drinksChanged();
    void ui_plot_max_valueChanged();
    void ui_current_party_idChanged();

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
