#ifndef DRINKCONTROLLER_H
#define DRINKCONTROLLER_H

#include <QObject>
#include <QVariant>
#include <drinq-lib_global.h>

#include "models/drink.h"

class QSettings;

namespace drinq::controllers {
class DatabaseControllerInterface;


class DRINQLIB_EXPORT DrinkController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<drinq::models::DrinkType> ui_drinkTypes READ ui_drinkTypes NOTIFY drinkTypesChanged )
    Q_PROPERTY(int ui_currentDrinkTypeIndex MEMBER m_currentDrinkTypeIndex NOTIFY currentDrinkTypeIndexChanged)
    Q_PROPERTY(QString ui_currentDrinkType MEMBER m_currentDrinkType NOTIFY currentDrinkTypeChanged)
    Q_PROPERTY(int ui_currentDrinkAmountMl MEMBER m_currentDrinkAmountMl NOTIFY currentDrinkAmountMlChanged)

public:
    explicit DrinkController(QObject *parent = nullptr, drinq::controllers::DatabaseControllerInterface* db = nullptr, QSettings* settings = nullptr);
    virtual ~DrinkController();

    Q_INVOKABLE QQmlListProperty<drinq::models::DrinkType> ui_drinkTypes();
    Q_INVOKABLE QString type(QVariant id);

public slots:
    void addDrinkType();
    void setCurrentDrinkProperties(int index, unsigned int amount_ml);

signals:
    void drinkTypesChanged();
    void currentDrinkTypeIndexChanged();
    void currentDrinkAmountMlChanged();
    void currentDrinkTypeChanged();

private:
    void createDrinkTypes();

public:
    drinq::controllers::DatabaseControllerInterface* m_db;
//    QVariant m_currentPartyId;
    QList<drinq::models::DrinkType*> m_drinkTypes;
    int m_currentDrinkTypeIndex = 0;
    QVariant m_currentDrinkTypeId;
    QString m_currentDrinkType;
    unsigned int m_currentDrinkAmountMl = 50;
    QSettings* m_settings;

};

}

#endif // DRINKCONTROLLER_H
