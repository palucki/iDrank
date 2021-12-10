#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QScopedPointer>

#include "controllers/databasecontrollerinterface.h"

#include "data/entity.h"

#include <drinq-lib_global.h>

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT DatabaseController : public DatabaseControllerInterface
{
    Q_OBJECT
public:
    explicit DatabaseController(QObject *parent = nullptr);
    ~DatabaseController();

    bool deleteRow(const QString& tableName, const QString& id) const override;
    QJsonArray find(const QString& tableName, const QString& searchText) const override;
    QJsonObject readRow(const QString& tableName, const QString& id) const override;
    bool updateRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const override;

    QJsonObject readParty(unsigned int id) override;

    QVariant getLastId(const QString& tableName) override;
    bool createRow(const QString& tableName, const QJsonObject& jsonObject) const override;

    bool create(data::EntityLite& e) override;
    bool update(const data::EntityLite& e) override;
    bool get(data::EntityLite &e) override;
    bool remove(data::EntityLite &e) override;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};


}
}
#endif // DATABASECONTROLLER_H
