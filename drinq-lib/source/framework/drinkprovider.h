#pragma once

#include <QObject>
#include <drinq-lib_global.h>
#include "models/drink.h"

namespace drinq::controllers {
class DatabaseControllerInterface;
}

namespace drinq::models {
class Drink2;
}

//class QAbstractSeries;

class DRINQLIB_EXPORT DrinkProvider : public QObject
{
    Q_OBJECT
public:
    DrinkProvider(drinq::controllers::DatabaseControllerInterface* db = nullptr);
    ~DrinkProvider() = default;

    Q_INVOKABLE QVariantList/*<drinq::models::Drink2>*/ getUIDrinksList(QVariant partyId);
    QList<drinq::models::Drink2*> getDrinksList(QVariant partyId);

//    Q_INVOKABLE void update(QAbstractSeries *series);
private:
    drinq::controllers::DatabaseControllerInterface* m_db = nullptr;
    QList<drinq::models::Drink2*> m_drinks;
};
