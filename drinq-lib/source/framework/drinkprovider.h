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

class DRINQLIB_EXPORT DrinkProvider : public QObject
{
    Q_OBJECT
public:
    DrinkProvider(drinq::controllers::DatabaseControllerInterface* db = nullptr);
    ~DrinkProvider() = default;

    Q_INVOKABLE QVariantList getUIDrinksList(QVariant partyId);
    QList<drinq::models::Drink2*> getDrinksList(QVariant partyId);

private:
    drinq::controllers::DatabaseControllerInterface* m_db = nullptr;
    QList<drinq::models::Drink2*> m_drinks;
};
