#pragma once

#include <QObject>
//#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
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
    PartyPlotter(QObject* parent = nullptr);
    virtual ~PartyPlotter();
public slots:
    void plot(QVariant party_id) const;

    // void setSeries(QAbstractSeries* partyStartEndSeries,
    //                QAbstractSeries* drinkSeries1,
    //                QAbstractSeries* drinkSeries2,
    //                QAbstractSeries* drinkSeries3);
    
    void addSeries(QAbstractSeries* series);
    void setAxes(QAbstractAxis* xAxis, QAbstractAxis* yAxis);
    void toggleVisibility(const QString& series_name);

    // void update(QVariant partyId);

private:
    // DrinkProvider m_drinkProvider;
    // drinq::controllers::DatabaseControllerInterface* m_database_controller{nullptr};
    // QScatterSeries* mPartyStartEndSeries{nullptr};
    QMap<QString, QXYSeries*> mDrinksSeriesMap;
    // QXYSeries* mDrinksSeries2 {nullptr};
    // QXYSeries* mDrinksSeries3 {nullptr};
    QDateTimeAxis* mDateTimeAxis{nullptr};
    QValueAxis* mValueAxis{nullptr};

};

