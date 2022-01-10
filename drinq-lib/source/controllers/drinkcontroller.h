#ifndef DRINKCONTROLLER_H
#define DRINKCONTROLLER_H

#include <QObject>
#include <QVariant>
#include <drinq-lib_global.h>

#include "models/drink.h"

namespace drinq::controllers {
class DatabaseControllerInterface;


class DRINQLIB_EXPORT DrinkController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<drinq::models::DrinkType> ui_drinkTypes READ ui_drinkTypes NOTIFY drinkTypesChanged )
public:
    explicit DrinkController(QObject *parent = nullptr, drinq::controllers::DatabaseControllerInterface* db = nullptr);
    virtual ~DrinkController();

    Q_INVOKABLE QQmlListProperty<drinq::models::DrinkType> ui_drinkTypes();

public slots:
    bool addDrink();
    void setPartyId(const QVariant& partyId);

    void addDrinkType();
    void setCurrentDrinkProperties(int index, unsigned int amount_ml);

signals:
    void drinkTypesChanged();

    //connected to party controller to update drinks count
    void drinkAdded();

private:
    drinq::controllers::DatabaseControllerInterface* m_db;
    QVariant m_currentPartyId;
    QList<drinq::models::DrinkType*> m_drinkTypes;
    int m_currentDrinkTypeIndex = 0;
    unsigned int m_currentDrinkAmountMl = 0;
};

}

#endif // DRINKCONTROLLER_H
