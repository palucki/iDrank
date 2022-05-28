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

void PartyPlotter::setSeries(QAbstractSeries *series)
{
    if(series)
    {
        QAreaSeries* area_series = static_cast<QAreaSeries*>(series);
        QXYSeries *xySeries = static_cast<QXYSeries *>(area_series->upperSeries());
        mDrinksSeries = xySeries;
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

void PartyPlotter::update(QVariant partyId)
{
    if(!mDrinksSeries || !mDateTimeAxis || !mValueAxis)
    {
        qDebug() << "No series intialized, skipping update in PartyPlotter";
        return;
    }

    auto drinks = m_drinkProvider.getDrinksList(partyId);

    if(drinks.isEmpty())
    {
        qDebug() << "No drinks, skipping update in party plotter";

        mDateTimeAxis->setMin(QDateTime::currentDateTime().addSecs(-600));
        mDateTimeAxis->setMax(QDateTime::currentDateTime().addSecs(+600));

        mValueAxis->setMin(0);
        mValueAxis->setMax(1000);

        return;
    }

    //drink provider fetches from newest
    std::reverse(drinks.begin(), drinks.end());

    mDateTimeAxis->setMin(drinks.first()->m_timestamp.addSecs(-600));
    mDateTimeAxis->setMax(drinks.last()->m_timestamp.addSecs(+600));


    mValueAxis->setMin(0);
    mValueAxis->setMax(1000);

    qreal current_sum = 0.0;
    QVector<QPointF> drink_points;

    for(const auto& d : drinks)
    {
        drink_points.append({static_cast<qreal>(d->m_timestamp.toMSecsSinceEpoch()),
                             static_cast<qreal>(current_sum)});
        current_sum += d->m_amount_ml;
//        qDebug() << "Plotter added " << d->m_amount_ml << " ml at " << d->m_timestamp << " current sum " << current_sum;
    }

    // Use replace instead of clear + append, it's optimized for performance
    mDrinksSeries->replace(drink_points);
}
