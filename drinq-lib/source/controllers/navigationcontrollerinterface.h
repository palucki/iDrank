#ifndef NAVIGATIONCONTROLLERINTERFACE_H
#define NAVIGATIONCONTROLLERINTERFACE_H

#include <QObject>

#include <drinq-lib_global.h>
#include <models/drink.h>

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT NavigationControllerInterface : public QObject
{
    Q_OBJECT
public:
    explicit NavigationControllerInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~NavigationControllerInterface() {}

signals:
    void goCreateClientView();
    void goDashboardView();
    void goEditClientView(drinq::models::Client* client);
    void goFindClientView();
};

}}
#endif // NAVIGATIONCONTROLLERINTERFACE_H
