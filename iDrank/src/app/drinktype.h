#pragma once 

#include <optional>
#include <QObject>

class DrinkType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant ui_id MEMBER m_id CONSTANT)
    Q_PROPERTY(QString ui_name MEMBER m_name CONSTANT)
    Q_PROPERTY(int ui_default_amount_ml MEMBER m_default_amount_ml CONSTANT)
    Q_PROPERTY(double ui_percentage MEMBER m_percentage CONSTANT)

public:
    explicit DrinkType(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~DrinkType() override {}

    static QList<DrinkType*> getDrinkTypes() 
    {
        QList<DrinkType*> drink_types;

        QSqlQuery query;
        query.prepare("SELECT id, name, default_amount_ml, percentage FROM drink_type");

        if(!query.exec())
        {
            qWarning() << "DrinkType::getDrinkTypes - ERROR: " << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        while(query.next())
        {
            auto* dt = new DrinkType;
            dt->m_id = query.value(0);
            dt->m_name = query.value(1).toString();
            dt->m_default_amount_ml = query.value(2).toInt();
            dt->m_percentage = query.value(3).toDouble();
            drink_types.append(dt);
        }

        return drink_types;
    }

    static std::optional<QVariant> add(const QString& name, int default_amount_ml, double percentage)
    {
        QSqlQuery query;
        query.prepare(QString("INSERT INTO drink_type (name, default_amount_ml, percentage)"
                              " VALUES (:name, :default_amount_ml, :percentage)"));

        query.bindValue(":name", name);
        query.bindValue(":default_amount_ml", default_amount_ml);
        query.bindValue(":percentage", percentage);

        if(!query.exec())
        {
            qWarning() << "DrinkType::add - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return {};
        }

        const auto drink_type_id = query.lastInsertId();
        return drink_type_id;
    }

    static bool remove(QVariant drink_type_id)
    {
        QSqlQuery query;
        query.prepare(QString("DELETE FROM drink_type WHERE id = :id"));
        query.bindValue(":id", drink_type_id);

        if(!query.exec())
        {
            qWarning() << "DrinkType::remove - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return false;
        }

        return true;
    }

    static bool update(QVariant id, QString name, int default_amount_ml, double percentage)
    {
        QSqlQuery query;
        query.prepare(QString("UPDATE drink_type SET "
                              "name = :name, default_amount_ml = :default_amount_ml, percentage = :percentage "
                              "WHERE id = :id"));

        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":default_amount_ml", default_amount_ml);
        query.bindValue(":percentage", percentage);

        if(!query.exec())
        {
            qWarning() << "DrinkType::update - ERROR:" << query.lastError().text() << " in query " << query.executedQuery();
            return false;
        }

        return true;
    }

public:
    QVariant m_id; //replace with base class like DatabaseObject
    QString m_name{};
    int m_default_amount_ml{};
    double m_percentage{}; //ABV - alcohol by volume
};