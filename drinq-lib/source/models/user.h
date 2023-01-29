#pragma once

#include <QObject>

#include "drinq-lib_global.h"

namespace drinq {
namespace models {

class DRINQLIB_EXPORT User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int ui_id MEMBER id CONSTANT)
    Q_PROPERTY(QString ui_name MEMBER m_name CONSTANT)
    Q_PROPERTY(QString ui_email MEMBER m_email CONSTANT)
    Q_PROPERTY(bool ui_involved MEMBER m_involved NOTIFY foo)

signals:
    void foo();

public:
    User(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~User() = default;

    int id;
    QString m_name;
    QString m_email;
    bool m_involved = false; //this is not from db
};

}
}
