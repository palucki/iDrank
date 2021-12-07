#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QScopedPointer>

#include "controllers/databasecontrollerinterface.h"

#include <drinq-lib_global.h>

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT DatabaseController : public DatabaseControllerInterface
{
    Q_OBJECT
public:
    explicit DatabaseController(QObject *parent = nullptr);
    ~DatabaseController();
    bool createRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const override;
    bool deleteRow(const QString& tableName, const QString& id) const override;
    QJsonArray find(const QString& tableName, const QString& searchText) const override;
    QJsonObject readRow(const QString& tableName, const QString& id) const override;
    bool updateRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const override;

    QVariant getLastId(const QString& tableName) override;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};


}
}
#endif // DATABASECONTROLLER_H
