#ifndef DATABASECONTROLLERINTERFACE_H
#define DATABASECONTROLLERINTERFACE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>
#include <drinq-lib_global.h>

namespace drinq::data {
class EntityLite;
}

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT DatabaseControllerInterface : public QObject
{
    Q_OBJECT
public:
    DatabaseControllerInterface(QObject* parent) : QObject(parent){}
    virtual ~DatabaseControllerInterface(){}
    virtual bool deleteRow(const QString& tableName, const QString& id) const = 0;
    virtual QJsonArray find(const QString& tableName, const QString& searchText) const = 0;
    virtual QJsonObject readRow(const QString& tableName, const QString& id) const = 0;
    virtual bool updateRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const = 0;

    virtual bool createRow(const QString& tableName, const QJsonObject& jsonObject) const = 0;

    virtual QJsonObject readParty(unsigned int id = 0) = 0;

    virtual QVariant getLastId(const QString& tableName) = 0;

    virtual bool create(data::EntityLite& e) = 0;
    virtual bool update(const data::EntityLite& e) = 0;
    virtual bool get(data::EntityLite &e) = 0;
    virtual bool remove(data::EntityLite &e) = 0;

    virtual QList<QVariantList> execQuery(const QString& sql, bool& ok) = 0;

    virtual QList<data::EntityLite> getAll(const data::EntityLite& e, const QString& where = {}) = 0;

    virtual int count(const data::EntityLite& e, const QString& where = {}) = 0;
};

}}
#endif // DATABASECONTROLLERINTERFACE_H
