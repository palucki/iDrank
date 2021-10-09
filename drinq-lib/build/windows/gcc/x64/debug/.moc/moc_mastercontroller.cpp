/****************************************************************************
** Meta object code from reading C++ file 'mastercontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../source/controllers/mastercontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mastercontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_drinq__controllers__MasterController_t {
    QByteArrayData data[15];
    char stringdata0[372];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_drinq__controllers__MasterController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_drinq__controllers__MasterController_t qt_meta_stringdata_drinq__controllers__MasterController = {
    {
QT_MOC_LITERAL(0, 0, 36), // "drinq::controllers::MasterCon..."
QT_MOC_LITERAL(1, 37, 12), // "selectClient"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 22), // "drinq::models::Client*"
QT_MOC_LITERAL(4, 74, 6), // "client"
QT_MOC_LITERAL(5, 81, 17), // "ui_welcomeMessage"
QT_MOC_LITERAL(6, 99, 23), // "ui_navigationController"
QT_MOC_LITERAL(7, 123, 50), // "drinq::controllers::Navigatio..."
QT_MOC_LITERAL(8, 174, 20), // "ui_commandController"
QT_MOC_LITERAL(9, 195, 47), // "drinq::controllers::CommandCo..."
QT_MOC_LITERAL(10, 243, 21), // "ui_databaseController"
QT_MOC_LITERAL(11, 265, 48), // "drinq::controllers::DatabaseC..."
QT_MOC_LITERAL(12, 314, 12), // "ui_newClient"
QT_MOC_LITERAL(13, 327, 15), // "ui_clientSearch"
QT_MOC_LITERAL(14, 343, 28) // "drinq::models::ClientSearch*"

    },
    "drinq::controllers::MasterController\0"
    "selectClient\0\0drinq::models::Client*\0"
    "client\0ui_welcomeMessage\0"
    "ui_navigationController\0"
    "drinq::controllers::NavigationControllerInterface*\0"
    "ui_commandController\0"
    "drinq::controllers::CommandControllerInterface*\0"
    "ui_databaseController\0"
    "drinq::controllers::DatabaseControllerInterface*\0"
    "ui_newClient\0ui_clientSearch\0"
    "drinq::models::ClientSearch*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_drinq__controllers__MasterController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       6,   22, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // properties: name, type, flags
       5, QMetaType::QString, 0x00095401,
       6, 0x80000000 | 7, 0x00095409,
       8, 0x80000000 | 9, 0x00095409,
      10, 0x80000000 | 11, 0x00095409,
      12, 0x80000000 | 3, 0x00095409,
      13, 0x80000000 | 14, 0x00095409,

       0        // eod
};

void drinq::controllers::MasterController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MasterController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectClient((*reinterpret_cast< drinq::models::Client*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::models::Client* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::controllers::CommandControllerInterface* >(); break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::controllers::DatabaseControllerInterface* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::controllers::NavigationControllerInterface* >(); break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::models::Client* >(); break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::models::ClientSearch* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MasterController *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->welcomeMessage(); break;
        case 1: *reinterpret_cast< drinq::controllers::NavigationControllerInterface**>(_v) = _t->navigationController(); break;
        case 2: *reinterpret_cast< drinq::controllers::CommandControllerInterface**>(_v) = _t->commandController(); break;
        case 3: *reinterpret_cast< drinq::controllers::DatabaseControllerInterface**>(_v) = _t->databaseController(); break;
        case 4: *reinterpret_cast< drinq::models::Client**>(_v) = _t->newClient(); break;
        case 5: *reinterpret_cast< drinq::models::ClientSearch**>(_v) = _t->clientSearch(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject drinq::controllers::MasterController::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_drinq__controllers__MasterController.data,
    qt_meta_data_drinq__controllers__MasterController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *drinq::controllers::MasterController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *drinq::controllers::MasterController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_drinq__controllers__MasterController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int drinq::controllers::MasterController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
