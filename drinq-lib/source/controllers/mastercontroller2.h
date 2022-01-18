#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <drinq-lib_global.h>
#include <controllers/databasecontrollerinterface.h>
#include <models/drink.h>

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT MasterController2 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<drinq::models::Party2> ui_parties READ ui_parties NOTIFY ui_partiesChanged )
public:
    explicit MasterController2(QObject *parent = nullptr, drinq::controllers::DatabaseControllerInterface* dbController = nullptr);
    ~MasterController2();

    Q_INVOKABLE QQmlListProperty<drinq::models::Party2> ui_parties();

signals:
    void ui_partiesChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}
#endif // MASTERCONTROLLER_H
