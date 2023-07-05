#pragma once

#include <QObject>
//#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

#include "userscontroller.h"

QT_USE_NAMESPACE

/*!
 *  This class is used for plotting party statistics (alcohol consumption over time).
 *
 *  The X axis is in range (party_start_time, last_alcohol_consumed_timestamp).
 *  If there are no drinks consumed yet, the latter is replaced with current time.
 *
 *  The Y axis is in range (0, alcohol consumed) ml.
 *  If there are no drinks consumed yet, the latter is replaced with 100.
 */

class PartyPlotter : public QObject
{
    Q_OBJECT
public:
    PartyPlotter(UsersController& users_controller, QObject* parent = nullptr);
    virtual ~PartyPlotter();
public slots:
    void reset();
    void plot(QVariant party_id) const;
    void addSeries(QAbstractSeries* series);
    void setAxes(QAbstractAxis* xAxis, QAbstractAxis* yAxis);
    void toggleVisibility(const QString& series_name);

private:
    QMap<QString, QXYSeries*> mDrinksSeriesMap;
    QDateTimeAxis* mDateTimeAxis{nullptr};
    QValueAxis* mValueAxis{nullptr};
    UsersController& m_users_controller;
};

