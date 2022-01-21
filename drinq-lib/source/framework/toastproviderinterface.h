#pragma once

#include <QObject>
#include <drinq-lib_global.h>
#include "toast.h"

class DRINQLIB_EXPORT ToastProviderInterface : public QObject
{
    Q_OBJECT
public:
    explicit ToastProviderInterface(QObject *parent = nullptr) : QObject(parent) {};
    virtual ~ToastProviderInterface() override = default;

    Q_INVOKABLE virtual Toast* randomToast() = 0;
};
