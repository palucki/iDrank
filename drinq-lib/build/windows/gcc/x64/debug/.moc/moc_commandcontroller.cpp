/****************************************************************************
** Meta object code from reading C++ file 'commandcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../source/controllers/commandcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'commandcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_drinq__controllers__CommandController_t {
    QByteArrayData data[9];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_drinq__controllers__CommandController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_drinq__controllers__CommandController_t qt_meta_stringdata_drinq__controllers__CommandController = {
    {
QT_MOC_LITERAL(0, 0, 37), // "drinq::controllers::CommandCo..."
QT_MOC_LITERAL(1, 38, 26), // "onCreateClientSaveExecuted"
QT_MOC_LITERAL(2, 65, 0), // ""
QT_MOC_LITERAL(3, 66, 26), // "onFindClientSearchExecuted"
QT_MOC_LITERAL(4, 93, 24), // "onEditClientSaveExecuted"
QT_MOC_LITERAL(5, 118, 26), // "onEditClientDeleteExecuted"
QT_MOC_LITERAL(6, 145, 17), // "setSelectedClient"
QT_MOC_LITERAL(7, 163, 22), // "drinq::models::Client*"
QT_MOC_LITERAL(8, 186, 6) // "client"

    },
    "drinq::controllers::CommandController\0"
    "onCreateClientSaveExecuted\0\0"
    "onFindClientSearchExecuted\0"
    "onEditClientSaveExecuted\0"
    "onEditClientDeleteExecuted\0setSelectedClient\0"
    "drinq::models::Client*\0client"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_drinq__controllers__CommandController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void drinq::controllers::CommandController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CommandController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onCreateClientSaveExecuted(); break;
        case 1: _t->onFindClientSearchExecuted(); break;
        case 2: _t->onEditClientSaveExecuted(); break;
        case 3: _t->onEditClientDeleteExecuted(); break;
        case 4: _t->setSelectedClient((*reinterpret_cast< drinq::models::Client*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::models::Client* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject drinq::controllers::CommandController::staticMetaObject = { {
    &CommandControllerInterface::staticMetaObject,
    qt_meta_stringdata_drinq__controllers__CommandController.data,
    qt_meta_data_drinq__controllers__CommandController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *drinq::controllers::CommandController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *drinq::controllers::CommandController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_drinq__controllers__CommandController.stringdata0))
        return static_cast<void*>(this);
    return CommandControllerInterface::qt_metacast(_clname);
}

int drinq::controllers::CommandController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CommandControllerInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
