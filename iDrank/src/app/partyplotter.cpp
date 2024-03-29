#include "partyplotter.h"

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChartView>

#include <iostream>

#include "party.h"
#include "user.h"
#include "drink.h"

QT_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

PartyPlotter::PartyPlotter(UsersController& users_controller, QObject *parent) 
    : QObject(parent)
    , m_users_controller(users_controller)
{
}

PartyPlotter::~PartyPlotter()
{
}

void PartyPlotter::plot(QVariant party_id) const
{
    // std::cout << "plot using axis" << mDateTimeAxis << " " << mValueAxis << " party " << party_id.toString().toStdString() << '\n';

    const auto users_name_map = m_users_controller.getUsersNameMap(true);

    int highest_sum = 0;
    QDateTime party_start_ts = Party::getStartedTime(party_id);
    QDateTime last_drink_ts;

    //TODO: set axisX->setTickCount(10); - consider fixed ticks? always 5? and distirbute them accordingly
    //TODO: axisX->setLabelFormat("%.2f");

    for(auto it = users_name_map.begin(); it != users_name_map.end(); ++it)
    {
        const auto user_id = it.key();
        const auto name = it.value();

        // std::cout << "user id: " << user_id << " name " << name.toStdString() << '\n';

        auto drinks = Drink::getDrinksForUserInParty(user_id, party_id);

        if(drinks.isEmpty())
        {
            continue;
        }

        qreal current_sum = 0.0;
        QVector<QPointF> drink_points;
        drink_points.append({static_cast<qreal>(party_start_ts.toMSecsSinceEpoch()), static_cast<qreal>(current_sum)});
        
        for(auto d : drinks)
        {
            // std::cout << "drink id " << d->m_id.toInt() << " amount " << d->m_amount_ml << '\n';
            current_sum += d->m_amount_ml;
            drink_points.append({static_cast<qreal>(d->m_timestamp.toMSecsSinceEpoch()), static_cast<qreal>(current_sum)});
        }

        auto* user_series = mDrinksSeriesMap[name];
        if(!user_series)
        {
            std::cout << "Invalid series for user " << name.toStdString() << '\n';
            return;
        }

        if(highest_sum < current_sum)
        {
            highest_sum = current_sum;
        }

        if(last_drink_ts < drinks.last()->m_timestamp)
        {
            last_drink_ts = drinks.last()->m_timestamp;
        }

        user_series->replace(drink_points);
    }

    mDateTimeAxis->setRange(party_start_ts, last_drink_ts.addSecs(300));
    mValueAxis->setRange(0, highest_sum * 1.1);
    mValueAxis->setTickCount(5);
}

void PartyPlotter::addSeries(QAbstractSeries* series) 
{
    const auto series_name = series->name();
    auto* xy_series = dynamic_cast<QXYSeries*>(series);
    
    if(!xy_series)
    {   std::cout << "Invalid XY series " << series_name.toStdString() << '\n';
        return;
    }

    std::cout << "Added series " << series_name.toStdString() << '\n';
    mDrinksSeriesMap[series_name] = xy_series;
}

void PartyPlotter::toggleVisibility(const QString& series_name)
{
    if(!mDrinksSeriesMap.contains(series_name))
    {
        std::cout << "ERROR: no such series name: " << series_name.toStdString() << '\n';
        return;
    }

    if(mDrinksSeriesMap[series_name] == nullptr)
    {
        std::cout << "ERROR: series name: " << series_name.toStdString() << " is null\n";
        return;
    }

    mDrinksSeriesMap[series_name]->setVisible(!mDrinksSeriesMap[series_name]->isVisible());
}

void PartyPlotter::setAxes(QAbstractAxis *xAxis, QAbstractAxis *yAxis)
{
    if(xAxis)
    {
        QDateTimeAxis* dateTimeAxis = static_cast<QDateTimeAxis*>(xAxis);
        mDateTimeAxis = dateTimeAxis;
    }

    if(yAxis)
    {
        QValueAxis* valueAxis = static_cast<QValueAxis*>(yAxis);
        mValueAxis = valueAxis;
    }
}

void PartyPlotter::reset()
{
    mDrinksSeriesMap.clear();
    mDateTimeAxis = nullptr;
    mValueAxis = nullptr;
}
