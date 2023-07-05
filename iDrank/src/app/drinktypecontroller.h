#pragma once 

#include <optional>
#include <QObject>
#include <QSettings>

#include "drinktype.h"

const QString DRINK_TYPES_IDS_ORDER = "drink_types_ids_order";
const QString DRINK_TYPE_KEY = "drink_type_id";
const QString DRINK_AMOUNT_KEY = "drink_amount_ml";

class DrinkTypeController : public QObject
{
    Q_PROPERTY(QList<DrinkType*> ui_drink_types READ getDrinkTypes NOTIFY ui_drink_types_changed)
    Q_PROPERTY(int ui_current_drink_amount_ml READ getCurrentDrinkAmountMl WRITE setCurrentDrinkAmountMl)

    Q_OBJECT
public:
    explicit DrinkTypeController(QSettings& settings, QObject* parent = nullptr) 
        : QObject(parent)
        , m_settings(settings) 
    {
        if(m_settings.contains(DRINK_AMOUNT_KEY))
        {
            m_current_drink_amount_ml = m_settings.value(DRINK_AMOUNT_KEY).toInt();
        }

        if(m_settings.contains(DRINK_TYPES_IDS_ORDER))
        {
            const QStringList drink_ids = m_settings.value(DRINK_TYPES_IDS_ORDER).toString().split(',');
            
            const auto drink_types = getDrinkTypes();
            m_drink_types.clear();

            QMap<int, DrinkType*> drink_type_by_id;
            for(auto* dt : qAsConst(drink_types))
            {
                drink_type_by_id[dt->m_id.toInt()] = dt;
            }

            for(const auto& dti : drink_ids)
            {
                if(!drink_type_by_id.contains(dti.toInt()))
                {
                    qDebug() << "ERROR while loading drink types from settings";
                    continue;
                }

                m_drink_types.append(drink_type_by_id[dti.toInt()]);
            }

            // those were not in the ordered list from settings
            for(auto* dt : qAsConst(drink_types))
            {
                if(!m_drink_types.contains(dt))
                {
                    m_drink_types.append(dt);
                }
            }

            emit ui_drink_types_changed();
        }
    }

    virtual ~DrinkTypeController() override {}

public slots:
    void update(int index, int id, const QString& name, int default_amount_ml, int percentage)
    {
        if(!DrinkType::update(id, name, default_amount_ml, percentage))
        {
            std::cout << "Unable to update drink " << name.toStdString() << '\n';
        }

        const auto drink_types = DrinkType::getDrinkTypes();

        if(m_settings.contains(DRINK_TYPES_IDS_ORDER))
        {
            const QStringList drink_ids = m_settings.value(DRINK_TYPES_IDS_ORDER).toString().split(',', Qt::SkipEmptyParts);
            
            m_drink_types.clear();

            QMap<int, DrinkType*> drink_type_by_id;
            for(auto* dt : qAsConst(drink_types))
            {
                drink_type_by_id[dt->m_id.toInt()] = dt;
            }

            for(const auto& dti : drink_ids)
            {
                if(!drink_type_by_id.contains(dti.toInt()))
                {
                    qDebug() << "ERROR while loading drink types from settings";
                    continue;
                }

                m_drink_types.append(drink_type_by_id[dti.toInt()]);
            }

            // those were not in the ordered list from settings
            for(auto* dt : qAsConst(drink_types))
            {
                if(!m_drink_types.contains(dt))
                {
                    m_drink_types.append(dt);
                }
            }
        }
        else
        {
            m_drink_types = drink_types;
        }

        // emits signal drink types changed and saves to settings
        setCurrentDrinkType(index);
    }

    void add(const QString& name, int default_amount_ml, int percentage)
    {
        const auto id = DrinkType::add(name, default_amount_ml, percentage);

        if(!id)
        {
            std::cout << "ERROR unable to add drink type\n";
            return;
        }

        const auto new_drink = new DrinkType;
        new_drink->m_id = id->toInt();
        new_drink->m_name = name;
        new_drink->m_default_amount_ml = default_amount_ml;
        new_drink->m_percentage = percentage;

        m_drink_types.prepend(new_drink);

        // handle settings + prepend
        emit ui_drink_types_changed();
    }

    QList<DrinkType*> getDrinkTypes()
    {
        if(m_drink_types.isEmpty())
        {
            m_drink_types = DrinkType::getDrinkTypes();
            emit ui_drink_types_changed();
        }

        return m_drink_types;
    } 

    void setCurrentDrinkType(int current_drink_index)
    {
        auto* selected_drink = m_drink_types[current_drink_index];

        m_drink_types.removeAt(current_drink_index);
        m_drink_types.prepend(selected_drink);

        emit ui_drink_types_changed();

        QStringList drink_ids_ordered;
        for(const auto* dt : m_drink_types)
        {
            drink_ids_ordered.append(QString::number(dt->m_id.toInt()));
        }

        m_settings.setValue(DRINK_TYPES_IDS_ORDER, drink_ids_ordered.join(','));
    }

    int getCurrentDrinkAmountMl()
    {
        return m_current_drink_amount_ml;
    }

    void setCurrentDrinkAmountMl(int current_drink_amount_ml)
    {
        m_current_drink_amount_ml = current_drink_amount_ml;
        m_settings.setValue(DRINK_AMOUNT_KEY, m_current_drink_amount_ml);
    }

signals:
    void ui_drink_types_changed();

private:
    QSettings& m_settings;
    QList<DrinkType*> m_drink_types;
    int m_current_drink_amount_ml{0};
};