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

PartyPlotter::PartyPlotter(QObject *parent) : QObject(parent)
{
    // qRegisterMetaType<QAbstractSeries*>();
    // qRegisterMetaType<QAbstractAxis*>();
}

PartyPlotter::~PartyPlotter()
{
}

void PartyPlotter::plot(QVariant party_id) const
{
    std::cout << "plot using axis" << mDateTimeAxis << " " << mValueAxis << " party " << party_id.toString().toStdString() << '\n';

    const auto users_name_map = User::getUsersNameMap();

    int highest_sum = 0;
    QDateTime earliest_drink_ts{QDateTime::currentDateTime()};
    QDateTime last_drink_ts;

    for(auto it = users_name_map.begin(); it != users_name_map.end(); ++it)
    {
        const auto user_id = it.key();
        const auto name = it.value();

        std::cout << "user id: " << user_id << " name " << name.toStdString() << '\n';

        auto drinks = Drink::getDrinksForUserInParty(user_id, party_id);

        qreal current_sum = 0.0;
        QVector<QPointF> drink_points;

        for(auto d : drinks)
        {
            std::cout << "drink id " << d->m_id.toInt() << " amount " << d->m_amount_ml << '\n';
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

        if(earliest_drink_ts > drinks.first()->m_timestamp)
        {
            earliest_drink_ts = drinks.first()->m_timestamp;
        }

        if(last_drink_ts < drinks.last()->m_timestamp)
        {
            last_drink_ts = drinks.last()->m_timestamp;
        }

        user_series->replace(drink_points);
    }

    mDateTimeAxis->setRange(earliest_drink_ts.addSecs(-300), last_drink_ts);
    mValueAxis->setRange(0, highest_sum);
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

    mDrinksSeriesMap[series_name]->setVisible(!mDrinksSeriesMap[series_name]->isVisible());
}

//     QAbstractSeries* partyStartEndSeries,
//     QAbstractSeries* drinkSeries2,
//     QAbstractSeries* drinkSeries3)
// {
//     QList<QPair<QXYSeries**, QAbstractSeries*>> series_mapping{
//         {&mDrinksSeries1, drinkSeries1},
//         {&mDrinksSeries2, drinkSeries2},
//         {&mDrinksSeries3, drinkSeries3},
//     };

//     for(auto& sm : series_mapping)
//     {
//         if(sm.second)
//         {
//             QXYSeries *xySeries = static_cast<QXYSeries *>(sm.second);
//             *(sm.first) = xySeries;
//         }
//     }

//     if(partyStartEndSeries)
//     {
//         QScatterSeries* scatter_series = static_cast<QScatterSeries*>(partyStartEndSeries);
//         mPartyStartEndSeries = scatter_series;
//     }
// }

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

// void PartyPlotter::update(QVariant partyId)
// {
//     QList<QXYSeries*> series{mDrinksSeries1, mDrinksSeries2, mDrinksSeries3};

//     if(!series[0] || !series[1] || !series[2] || !mPartyStartEndSeries || !mDateTimeAxis || !mValueAxis)
//     {
//         qDebug() << "No series intialized, skipping update in PartyPlotter";
//         return;
//     }

//     auto* party = new drinq::models::Party2(this);
//     party->setId(partyId);
//     m_database_controller->get(*party);
//     party->update(party->toJson());

//     QDateTime party_started = party->m_started;
//     QDateTime partyEnded = party->m_ended;

//     if(!party_started.isValid())
//     {
//         qDebug() << "Will not update invalid party started";
//         return;
//     }

//     auto drinks = m_drinkProvider.getDrinksList(partyId);
//     QVector<QPointF> startEndPoints;
//     const auto current_time = QDateTime::currentDateTime();

//     startEndPoints.append({static_cast<qreal>(party_started.toMSecsSinceEpoch()),
//                            static_cast<qreal>(0)});
//     if(drinks.isEmpty())
//     {
//         mDateTimeAxis->setRange(party_started, current_time);
//         mValueAxis->setRange(0, 100);
//         series[0]->replace(startEndPoints);
//         series[1]->replace(startEndPoints);
//         series[2]->replace(startEndPoints);
//         return;
//     }

//     //drink provider fetches from newest
//     std::reverse(drinks.begin(), drinks.end());

//     qreal current_sum = 0.0;
//     QVector<QPointF> drink_points;


//     const auto drink_types = m_database_controller->getAll(drinq::models::DrinkType{this});
//     QMap<int, drinq::models::DrinkType::ConsumptionType> drink_type_map;
//     for(const auto& dt : drink_types)
//     {
//         drink_type_map.insert(dt.m_data["id"].toInt(),
//                               static_cast<drinq::models::DrinkType::ConsumptionType>(dt.m_data["consumption_type"].toInt()));
//     }

//     bool ok = false;
//     const auto result = m_database_controller->execQuery(QString(
//                             "SELECT DISTINCT user_id FROM drink "
//                             "LEFT JOIN drink_user_rel ON drink_user_rel.drink_id = drink.id "
//                             "WHERE party_id = %1 AND user_id IS NOT NULL "
//                             "ORDER BY user_id LIMIT 3;").arg(partyId.toInt()), ok);

//     if(!ok || result.isEmpty())
//         return;

//     const auto users = result.size();
//     qDebug() << "Found " << users << " users";

//     int cnt = 0;
//     int highest_sum = 0;

//     for(const auto& uid : result)
//     {
//         if(cnt > 2)
//             break;

//         drink_points.clear();
//         drink_points.append({static_cast<qreal>(party_started.toMSecsSinceEpoch()),
//                              static_cast<qreal>(0)});

//         current_sum = 0;
//         auto* current_series = series[cnt++];

//         const auto user_id = uid.first().toInt();
//         qDebug() << "User id " << user_id;

//         const auto user_drinks = m_database_controller->execQuery(QString(
//                              "SELECT timestamp, amount_ml "
//                              "FROM drink LEFT JOIN drink_user_rel ON drink_user_rel.drink_id = drink.id "
//                              "WHERE party_id = %1 AND user_id = %2;").arg(partyId.toInt()).arg(user_id), ok);

//         qDebug() << "Found " << user_drinks.size() << " user drinks";

//         for(const auto& d : user_drinks)
//         {
//             current_sum += d[1].toReal();
//             drink_points.append({static_cast<qreal>(d[0].toDateTime().toMSecsSinceEpoch()), static_cast<qreal>(current_sum)});
//         }

//         qDebug() << "Highest sum " << highest_sum << " current sum " << current_sum;

//         if(highest_sum <= current_sum)
//             highest_sum = current_sum;

//         current_series->replace(drink_points);
//     }
// //    for(const auto& d : drinks)
// //    {
// //        const auto consumption_type = drink_type_map[d->m_drink_type_id.toInt()];
// //        qDebug() << "Plotting drink types " << d->m_id << " with consumption type " << d->m_data["consumption_type"].toInt();
// //        if(consumption_type == drinq::models::DrinkType::ConsumptionType::Shot)
// //        {
// //            drink_points.append({static_cast<qreal>(d->m_timestamp.toMSecsSinceEpoch()),
// //                                 static_cast<qreal>(current_sum)});
// //            current_sum += d->m_amount_ml;
// //            drink_points.append({static_cast<qreal>(d->m_timestamp.toMSecsSinceEpoch()),
// //                                 static_cast<qreal>(current_sum)});
// //        }
// //        else
// //        {
// //            drink_points.append({static_cast<qreal>(d->m_timestamp.toMSecsSinceEpoch()),
// //                                 static_cast<qreal>(current_sum)});
// //            current_sum += d->m_amount_ml;
// //        }
// //    }

// //    if(!partyEnded.isNull() &&
// //       drink_type_map[drinks.last()->m_drink_type_id.toInt()] == drinq::models::DrinkType::ConsumptionType::Long)
// //    {
// //        drink_points.append({static_cast<qreal>(partyEnded.toMSecsSinceEpoch()),
// //                             static_cast<qreal>(current_sum)});
// //    }

//     mDateTimeAxis->setRange(party_started, drinks.last()->m_timestamp);
//     mValueAxis->setRange(0, highest_sum);
//     qDebug() << "Highest sum " << highest_sum;

//     // Use replace instead of clear + append, it's optimized for performance
// //    mDrinksSeries1->replace(drink_points);
// }
