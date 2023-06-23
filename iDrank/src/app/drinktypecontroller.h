#pragma once 

#include <optional>
#include <QObject>

#include "drinktype.h"

class DrinkTypeController : public QObject
{
    Q_PROPERTY(QList<DrinkType*> ui_drink_types READ getDrinkTypes NOTIFY ui_drink_types_changed)
    Q_OBJECT
public:
    explicit DrinkTypeController(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~DrinkTypeController() override {}

public slots:
    QList<DrinkType*> getDrinkTypes()
    {
        if(m_drink_types.isEmpty())
        {
            m_drink_types = DrinkType::getDrinkTypes();
            emit ui_drink_types_changed();
        }

        return m_drink_types;
    } 

signals:
    void ui_drink_types_changed();

private: 
    QList<DrinkType*> m_drink_types;
};