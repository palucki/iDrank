#ifndef DATABASECONTROLLERINTERFACE_H
#define DATABASECONTROLLERINTERFACE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>
#include <drinq-lib_global.h>

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT DatabaseControllerInterface : public QObject
{
    Q_OBJECT
public:
    DatabaseControllerInterface(QObject* parent) : QObject(parent){}
    virtual ~DatabaseControllerInterface(){}
    virtual bool createRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const = 0;
    virtual bool deleteRow(const QString& tableName, const QString& id) const = 0;
    virtual QJsonArray find(const QString& tableName, const QString& searchText) const = 0;
    virtual QJsonObject readRow(const QString& tableName, const QString& id) const = 0;
    virtual bool updateRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const = 0;

    virtual QVariant getLastId(const QString& tableName) = 0;
};

}}
#endif // DATABASECONTROLLERINTERFACE_H
