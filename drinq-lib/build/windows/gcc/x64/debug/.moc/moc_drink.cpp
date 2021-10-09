/****************************************************************************
** Meta object code from reading C++ file 'drink.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../source/models/drink.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drink.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_drinq__models__Client_t {
    QByteArrayData data[15];
    char stringdata0[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_drinq__models__Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_drinq__models__Client_t qt_meta_stringdata_drinq__models__Client = {
    {
QT_MOC_LITERAL(0, 0, 21), // "drinq::models::Client"
QT_MOC_LITERAL(1, 22, 19), // "appointmentsChanged"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 15), // "contactsChanged"
QT_MOC_LITERAL(4, 59, 10), // "addContact"
QT_MOC_LITERAL(5, 70, 15), // "ui_appointments"
QT_MOC_LITERAL(6, 86, 44), // "QQmlListProperty<drinq::model..."
QT_MOC_LITERAL(7, 131, 11), // "ui_contacts"
QT_MOC_LITERAL(8, 143, 40), // "QQmlListProperty<drinq::model..."
QT_MOC_LITERAL(9, 184, 12), // "ui_reference"
QT_MOC_LITERAL(10, 197, 29), // "drinq::data::StringDecorator*"
QT_MOC_LITERAL(11, 227, 7), // "ui_name"
QT_MOC_LITERAL(12, 235, 16), // "ui_supplyAddress"
QT_MOC_LITERAL(13, 252, 23), // "drinq::models::Address*"
QT_MOC_LITERAL(14, 276, 17) // "ui_billingAddress"

    },
    "drinq::models::Client\0appointmentsChanged\0"
    "\0contactsChanged\0addContact\0ui_appointments\0"
    "QQmlListProperty<drinq::models::Appointment>\0"
    "ui_contacts\0QQmlListProperty<drinq::models::Contact>\0"
    "ui_reference\0drinq::data::StringDecorator*\0"
    "ui_name\0ui_supplyAddress\0"
    "drinq::models::Address*\0ui_billingAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_drinq__models__Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       6,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       5,    0,   42,    2, 0x02 /* Public */,
       7,    0,   43,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    0x80000000 | 6,
    0x80000000 | 8,

 // properties: name, type, flags
       9, 0x80000000 | 10, 0x00095409,
      11, 0x80000000 | 10, 0x00095409,
      12, 0x80000000 | 13, 0x00095409,
      14, 0x80000000 | 13, 0x00095409,
       5, 0x80000000 | 6, 0x00495009,
       7, 0x80000000 | 8, 0x00495009,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       1,

       0        // eod
};

void drinq::models::Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->appointmentsChanged(); break;
        case 1: _t->contactsChanged(); break;
        case 2: _t->addContact(); break;
        case 3: { QQmlListProperty<drinq::models::Appointment> _r = _t->ui_appointments();
            if (_a[0]) *reinterpret_cast< QQmlListProperty<drinq::models::Appointment>*>(_a[0]) = std::move(_r); }  break;
        case 4: { QQmlListProperty<drinq::models::Contact> _r = _t->ui_contacts();
            if (_a[0]) *reinterpret_cast< QQmlListProperty<drinq::models::Contact>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::appointmentsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::contactsChanged)) {
                *result = 1;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::data::StringDecorator* >(); break;
        case 3:
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::models::Address* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< drinq::data::StringDecorator**>(_v) = _t->reference; break;
        case 1: *reinterpret_cast< drinq::data::StringDecorator**>(_v) = _t->name; break;
        case 2: *reinterpret_cast< drinq::models::Address**>(_v) = _t->supplyAddress; break;
        case 3: *reinterpret_cast< drinq::models::Address**>(_v) = _t->billingAddress; break;
        case 4: *reinterpret_cast< QQmlListProperty<drinq::models::Appointment>*>(_v) = _t->ui_appointments(); break;
        case 5: *reinterpret_cast< QQmlListProperty<drinq::models::Contact>*>(_v) = _t->ui_contacts(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject drinq::models::Client::staticMetaObject = { {
    &data::Entity::staticMetaObject,
    qt_meta_stringdata_drinq__models__Client.data,
    qt_meta_data_drinq__models__Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *drinq::models::Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *drinq::models::Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_drinq__models__Client.stringdata0))
        return static_cast<void*>(this);
    return data::Entity::qt_metacast(_clname);
}

int drinq::models::Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = data::Entity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
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

// SIGNAL 0
void drinq::models::Client::appointmentsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void drinq::models::Client::contactsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
