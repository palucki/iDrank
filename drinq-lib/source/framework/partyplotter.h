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

    void update(QVariant partyId, QDateTime partyStarted, QDateTime partyEnded = {});

private:
    DrinkProvider m_drinkProvider;
    QScatterSeries* mPartyStartEndSeries{nullptr};
    QXYSeries* mDrinksSeries {nullptr};
    QDateTimeAxis* mDateTimeAxis{nullptr};
    QValueAxis* mValueAxis{nullptr};

};

