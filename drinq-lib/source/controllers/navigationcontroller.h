#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>

#include "navigationcontrollerinterface.h"

#include <drinq-lib_global.h>
#include <models/drink.h>

namespace drinq {
namespace controllers {

class DRINQLIB_EXPORT NavigationController : public NavigationControllerInterface
{
    Q_OBJECT

public:
    explicit NavigationController(QObject* parent = nullptr)
        : NavigationControllerInterface(parent) {}
};

}
}

#endif // NAVIGATIONCONTROLLER_H
