#include "partyplotter.h"

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

PartyPlotter::PartyPlotter(QObject *parent, drinq::controllers::DatabaseControllerInterface *db)
    : QObject(parent),
      m_drinkProvider(db)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
}

PartyPlotter::~PartyPlotter()
{
}

void PartyPlotter::setSeries(QAbstractSeries *drinksSeries, QAbstractSeries* partyStartEndSeries)
{
    if(drinksSeries)
    {
        QAreaSeries* area_series = static_cast<QAreaSeries*>(drinksSeries);
        QXYSeries *xySeries = static_cast<QXYSeries *>(area_series->upperSeries());
        mDrinksSeries = xySeries;
    }

    if(partyStartEndSeries)
    {
        QScatterSeries* scatter_series = static_cast<QScatterSeries*>(partyStartEndSeries);
        mPartyStartEndSeries = scatter_series;
    }
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

void PartyPlotter::update(QVariant partyId, QDateTime party_started, QDateTime partyEnded)
{
    if(!mDrinksSeries || !mPartyStartEndSeries || !mDateTimeAxis || !mValueAxis)
    {
        qDebug() << "No series intialized, skipping update in PartyPlotter";
        return;
    }

    if(!party_started.isValid())
    {
        qDebug() << "Will not update invalid party started";
        return;
    }

    auto drinks = m_drinkProvider.getDrinksList(partyId);
    QVector<QPointF> startEndPoints;
    const auto current_time = QDateTime::currentDateTime();

    startEndPoints.append({static_cast<qreal>(party_started.toMSecsSinceEpoch()),
                           static_cast<qreal>(0)});
    if(drinks.isEmpty())
    {
        mDateTimeAxis->setRange(party_started, current_time);
        mValueAxis->setRange(0, 100);
        mDrinksSeries->replace(startEndPoints);
        return;
    }

    //drink provider fetches from newest
    std::reverse(drinks.begin(), drinks.end());

    qreal current_sum = 0.0;
    QVector<QPointF> drink_points;

    drink_points.append({static_cast<qreal>(party_started.toMSecsSinceEpoch()),
                         static_cast<qreal>(0)});

    for(const auto& d : drinks)
    {
        //depending on the drink type either apply both points, or only the latter one
//        drink_points.append({static_cast<qreal>(d->m_timestamp.toMSecsSinceEpoch()),
//                             static_cast<qreal>(current_sum)});

        current_sum += d->m_amount_ml;
        drink_points.append({static_cast<qreal>(d->m_timestamp.toMSecsSinceEpoch()),
                             static_cast<qreal>(current_sum)});
    }

    mDateTimeAxis->setRange(party_started, drinks.last()->m_timestamp);
    mValueAxis->setRange(0, current_sum);

    // Use replace instead of clear + append, it's optimized for performance
    mDrinksSeries->replace(drink_points);
}
