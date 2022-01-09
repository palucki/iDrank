#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QObject>
#include <QScopedPointer>
#include <QDebug>
#include <drinq-lib_global.h>
#include <data/datadecorator.h>
#include <data/entitycollection.h>

namespace drinq {
namespace data {

class StringDecorator;

class DRINQLIB_EXPORT EntityLite : public QObject
{
    Q_OBJECT
public:
    EntityLite(const QString& tableName, QObject* parent) : QObject(parent), m_tableName(tableName)
    {
    }

    EntityLite(const EntityLite& e) : EntityLite(e.m_tableName, e.parent())
    {
        qDebug() << "Copy ctor";
        m_fields = e.m_fields;
        m_bindableFields = e.m_bindableFields;
        m_data = e.m_data;
//        update(e.toJson());
    }

    EntityLite& operator=(const EntityLite& e)
    {
        qDebug() << "SHOULDNT BE HERE Assignment operator";
        if(this == &e)
        {
            return *this;
        }

//        EntityLite tmp(e);
//        std::swap(*this, tmp);

        return *this;
    }

    void setId(const QVariant& id)
    {
        m_id = id;
        m_data["id"] = id;
    }

    void setFieldValue(const QString& key, const QVariant& value)
    {
        m_data[key] = value;
    }

    void addField(const QString& key, const QVariant& value)
    {
        if(key.isEmpty())
        {
            return;
        }

        if(!m_fields.contains(key))
        {
            m_fields.append(key);
        }

        if(!m_bindableFields.contains(":" + key))
        {
            m_bindableFields.append(":" + key);
        }

        m_data[key] = value;
    }

    virtual void update(const QJsonObject& src)
    {
        for(auto it = m_data.begin(); it != m_data.end(); ++it)
        {
            const auto key = it.key();
            if(src.contains(key))
            {
                it.value() = src[key];
            }
        }
    }

    QJsonObject toJson() const
    {
        QJsonObject obj;

        obj.insert("id", m_id.toJsonValue());

        for(const auto& f : m_fields)
        {
            obj.insert(f, m_data[f].toJsonValue());
        }

        return obj;
    }

    QString m_tableName;
    QStringList m_fields;
    QStringList m_bindableFields;
    QMap<QString, QVariant> m_data;
    QVariant m_id;
};

class DRINQLIB_EXPORT Entity : public QObject
{
    Q_OBJECT
public:
    Entity(QObject* parent = nullptr, const QString& key = "SomeEntityKey");
    Entity(QObject* parent, const QString& key, const QJsonObject& jsonObject);
    virtual ~Entity();
public:
    const QString& key() const;
    void update(const QJsonObject& jsonObject);
    virtual QJsonObject toJson() const;
    const QString& id() const;
signals:
    void childEntitiesChanged();
    void dataDecoratorsChanged();
    void childCollectionsChanged(const QString& collectionKey);
protected:
    Entity* addChild(Entity* entity, const QString& key);
    DataDecorator* addDataItem(DataDecorator* dataDecorator);
    EntityCollectionBase* addChildCollection(EntityCollectionBase* entityCollection);
    void setPrimaryKey(StringDecorator* primaryKey);
protected:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // ENTITY_H
