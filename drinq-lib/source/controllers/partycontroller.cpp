#include "partycontroller.h"

#include "databasecontrollerinterface.h"

#include "controllers/drinkcontroller.h"
#include "models/drink.h"

#include <QDebug>

//#include <QtCharts/QXYSeries>
//#include <QtCharts/QAbstractAxis>
//#include <QtCharts/QXYSeries>
//#include <QtCharts/QAreaSeries>

#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>


QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

PartyController::PartyController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db, drinq::controllers::DrinkController *drinksController)
    : QObject(parent), m_db(db), m_drinkController(drinksController)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();


}

PartyController::~PartyController()
{
}

QQmlListProperty<drinq::models::Drink2> PartyController::ui_drinks()
{
    return QQmlListProperty<drinq::models::Drink2>(this, m_drinks);
}

unsigned int PartyController::ui_plot_max_value()
{
    return 1000;
}

qint64 PartyController::secondsSinceLastDrink()
{
    if(m_drinks.empty())
    {
        return 0;
    }

    //because sorted in reverse order
    auto& last_drink = m_drinks.first();

    const qint64 diff_sec = last_drink->m_timestamp.secsTo(QDateTime::currentDateTime());
    return diff_sec;
}

void PartyController::startParty()
{
    m_drinks.clear();
    emit ui_drinksChanged();
    setDrinksCount(0);
}

void PartyController::setPartyId(QVariant id)
{
    m_currentPartyId = id;
    auto drinks = m_db->getAll(drinq::models::Drink2{this}, "WHERE party_id = " + m_currentPartyId.toString());

    qDebug() << "Found " << drinks.size() << " drinks";

    for(const auto& d : drinks)
    {
        qDebug() << d.toJson();
        m_drinks.append(new drinq::models::Drink2(d.toJson(), this));
    }

    std::sort(m_drinks.begin(), m_drinks.end(), [](drinq::models::Drink2* lhs, drinq::models::Drink2* rhs){
        return rhs->m_timestamp < lhs->m_timestamp;
    });

     setDrinksCount(drinks.count());
}

void PartyController::endParty()
{
    m_drinks.clear();
    emit ui_drinksChanged();
    setDrinksCount(0);
}

void PartyController::setDrinksCount(int count)
{
    qDebug() << "CURRENT COUnT " << count;
    m_current_drinks_count = count;

    emit ui_drinks_countChanged(m_current_drinks_count);
}

void PartyController::addDrink()
{
    qDebug() << "Latest party id " << m_currentPartyId;

    auto newDrink = new drinq::models::Drink2{this};
    newDrink->setPartyId(m_currentPartyId);
    newDrink->setDrinkTypeId(m_drinkController->m_currentDrinkTypeId);
    newDrink->setAmountMl(m_drinkController->m_currentDrinkAmountMl);

    if(m_db->create(*newDrink))
    {
        m_drinks.append(newDrink);
        std::sort(m_drinks.begin(), m_drinks.end(), [](drinq::models::Drink2* lhs, drinq::models::Drink2* rhs){
            return rhs->m_timestamp < lhs->m_timestamp;
        });

        emit ui_drinksChanged();
        setDrinksCount(m_current_drinks_count + 1);
        qDebug() << "PartyController -> drink added";
    }
    else
    {
        qDebug() << "PartyController -> drink not added !";
    }
}

void PartyController::deleteDrink(const QVariant &id)
{
    const auto it = std::find_if(m_drinks.cbegin(), m_drinks.cend(), [id](drinq::models::Drink2* d){
        return d->m_id == id;
    });

    if(it == m_drinks.cend())
    {
        qDebug() << "Unable to find and remove drink with id " << id;
        return;
    }

    auto* drink_ptr = *it;

    qDebug() << "Sanity check drink ptr id " << drink_ptr->m_id;
    qDebug() << "Sanity check last dirnk id " << m_drinks.back()->m_id;

    if(m_db->remove(*drink_ptr))
    {
        m_drinks.removeAll(drink_ptr);
        emit ui_drinksChanged();
        setDrinksCount(m_current_drinks_count - 1);
    }
}

void PartyController::update(QAbstractSeries* series)
{
    if (series) {
        QAreaSeries* area_series = static_cast<QAreaSeries*>(series);
//        QLineSeries* line_series = static_cast<QLineSeries*>(area_series->upperSeries());
        QXYSeries *xySeries = static_cast<QXYSeries *>(area_series->upperSeries());
//        m_index++;
//        if (m_index > m_data.count() - 1)
//            m_index = 0;

        qreal current_sum = 0.0;
        QVector<QPointF> drink_points;
        for(auto rit = m_drinks.rbegin(); rit != m_drinks.rend(); ++rit)
        {
            current_sum += (*rit)->m_amount_ml;
            drink_points.append({static_cast<qreal>((*rit)->m_timestamp.toMSecsSinceEpoch()),
                                 static_cast<qreal>(current_sum)});
        }

//        QVector<QPointF> points {
//            {20000, 10},
//            {10, 20},
//            {20, 40},
//            {30, 50},
//            {40, 90}
//        };
//            = m_data.at(m_index);
        // Use replace instead of clear + append, it's optimized for performance
        xySeries->replace(drink_points);
    }
}

QDateTime PartyController::plot_min()
{
    //reversed order
    //handle cases like no results, 1 result, multiple results, add some space from left and right, start with full hour etc.
    if(m_drinks.isEmpty())
    {
        return {};
    }

    return m_drinks.last()->m_timestamp;
}

QDateTime PartyController::plot_max()
{
    //reversed order
    //handle cases like no results, 1 result, multiple results, add some space from left and right, start with full hour etc.

    if(m_drinks.isEmpty())
    {
        return {};
    }

    return m_drinks.first()->m_timestamp;
}
