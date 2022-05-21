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
    Q_PROPERTY(unsigned int ui_plot_max_value READ ui_plot_max_value NOTIFY ui_plot_max_valueChanged)

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
    void update(QAbstractSeries *series);
    QDateTime plot_min();
    QDateTime plot_max();

signals:
    void ui_drinks_countChanged(int count);
    void ui_drinksChanged();
    void ui_plot_max_valueChanged();

private:
    void setDrinksCount(int count);

    drinq::controllers::DatabaseControllerInterface* m_db = nullptr;
    drinq::controllers::DrinkController* m_drinkController = nullptr;

    //DrinksProivder?

    //PartyController to tylko malutka klasa posiadajaca start i end party
    //cala reszta to bedzie Drinks Proviider albo cos w tym stylu
    QList<drinq::models::Drink2*> m_drinks;
    int m_current_drinks_count = 0;
    QVariant m_currentPartyId;
};
