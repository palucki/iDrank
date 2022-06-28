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

void PartyPlotter::update(QVariant partyId, QDateTime partyStarted, QDateTime partyEnded)
{
    if(!mDrinksSeries || !mPartyStartEndSeries || !mDateTimeAxis || !mValueAxis)
    {
        qDebug() << "No series intialized, skipping update in PartyPlotter";
        return;
    }

    auto drinks = m_drinkProvider.getDrinksList(partyId);
    QVector<QPointF> startEndPoints;

    if(drinks.isEmpty())
    {
        qDebug() << "No drinks, skipping update in party plotter";

        mDateTimeAxis->setRange(partyStarted.addSecs(-300), QDateTime::currentDateTime().addSecs(+600));
        mValueAxis->setRange(0, 1000);

        startEndPoints.append({static_cast<qreal>(partyStarted.toMSecsSinceEpoch()),
                               static_cast<qreal>(0)});

        mDrinksSeries->clear();
        mPartyStartEndSeries->replace(startEndPoints);
        return;
    }

    if(!partyStarted.isValid())
    {
        qDebug() << "Will not update invalid party started";
        return;
    }

    //drink provider fetches from newest
    std::reverse(drinks.begin(), drinks.end());

    mDateTimeAxis->setRange(partyStarted.addSecs(-300), drinks.last()->m_timestamp.addSecs(+600));
    mValueAxis->setRange(0, 1000);

    qreal current_sum = 0.0;
    QVector<QPointF> drink_points;

    drink_points.append({static_cast<qreal>(partyStarted.toMSecsSinceEpoch()),
                         static_cast<qreal>(0)});

    startEndPoints.append({static_cast<qreal>(partyStarted.toMSecsSinceEpoch()),
                           static_cast<qreal>(0)});

    for(const auto& d : drinks)
    {
        current_sum += d->m_amount_ml;

        drink_points.append({static_cast<qreal>(d->m_timestamp.toMSecsSinceEpoch()),
                             static_cast<qreal>(current_sum)});
//        qDebug() << "Plotter added " << d->m_amount_ml << " ml at " << d->m_timestamp << " current sum " << current_sum;
    }

    qDebug() << " FIXME party ended " << partyEnded;

    if(!partyEnded.isNull())
    {
        drink_points.append({static_cast<qreal>(partyEnded.toMSecsSinceEpoch()),
                             static_cast<qreal>(current_sum)});
        startEndPoints.append({static_cast<qreal>(partyEnded.toMSecsSinceEpoch()),
                             static_cast<qreal>(current_sum)});
    }

    // Use replace instead of clear + append, it's optimized for performance
    mDrinksSeries->replace(drink_points);
    mPartyStartEndSeries->replace(startEndPoints);
}
