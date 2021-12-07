#include "drinkcontroller.h"

#include "databasecontrollerinterface.h"

#include <QDebug>

DrinkController::DrinkController(QObject *parent, drinq::controllers::DatabaseControllerInterface *db)
    : QObject(parent), m_db(db)
{
    auto lastId = m_db->getLastId("drinks");
    if(lastId.isNull())
    {
        qDebug() << "NO drinks";
    }
}

DrinkController::~DrinkController()
{

}

bool DrinkController::addDrink()
{
    qDebug() << "Adding drink";
    return true;
}

bool DrinkController::resetCounter()
{
    qDebug() << "Resetting counter";
    return true;
}
