#pragma once

#include <drinq-lib_global.h>

#include <QObject>
//#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
QT_CHARTS_USE_NAMESPACE

#include "framework/drinkprovider.h"

/*!
 *  This class is used for plotting party statistics (alcohol consumption over time).
 *
 *  The X axis is in range (party_start_time, last_alcohol_consumed_timestamp).
 *  If there are no drinks consumed yet, the latter is replaced with current time.
 *
 *  The Y axis is in range (0, alcohol consumed) ml.
 *  If there are no drinks consumed yet, the latter is replaced with 100.
 */

namespace drinq::controllers {
class DatabaseControllerInterface;
}

class DRINQLIB_EXPORT PartyPlotter : public QObject
{
    Q_OBJECT
public:
    PartyPlotter(QObject* parent = nullptr, drinq::controllers::DatabaseControllerInterface *db = nullptr);
    virtual ~PartyPlotter();
public slots:
    void setSeries(QAbstractSeries* drinkSeries, QAbstractSeries* partyStartEndSeries);
    void setAxes(QAbstractAxis* xAxis, QAbstractAxis* yAxis);

    void update(QVariant partyId);

private:
    DrinkProvider m_drinkProvider;
    drinq::controllers::DatabaseControllerInterface* m_database_controller{nullptr};
    QScatterSeries* mPartyStartEndSeries{nullptr};
    QXYSeries* mDrinksSeries {nullptr};
    QDateTimeAxis* mDateTimeAxis{nullptr};
    QValueAxis* mValueAxis{nullptr};

};

