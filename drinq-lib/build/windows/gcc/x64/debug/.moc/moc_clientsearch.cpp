/****************************************************************************
** Meta object code from reading C++ file 'clientsearch.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../source/models/clientsearch.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientsearch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_drinq__models__ClientSearch_t {
    QByteArrayData data[7];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_drinq__models__ClientSearch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_drinq__models__ClientSearch_t qt_meta_stringdata_drinq__models__ClientSearch = {
    {
QT_MOC_LITERAL(0, 0, 27), // "drinq::models::ClientSearch"
QT_MOC_LITERAL(1, 28, 20), // "searchResultsChanged"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 13), // "ui_searchText"
QT_MOC_LITERAL(4, 64, 29), // "drinq::data::StringDecorator*"
QT_MOC_LITERAL(5, 94, 16), // "ui_searchResults"
QT_MOC_LITERAL(6, 111, 39) // "QQmlListProperty<drinq::model..."

    },
    "drinq::models::ClientSearch\0"
    "searchResultsChanged\0\0ui_searchText\0"
    "drinq::data::StringDecorator*\0"
    "ui_searchResults\0"
    "QQmlListProperty<drinq::models::Client>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_drinq__models__ClientSearch[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       2,   20, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, 0x80000000 | 4, 0x00095409,
       5, 0x80000000 | 6, 0x00495009,

 // properties: notify_signal_id
       0,
       0,

       0        // eod
};

void drinq::models::ClientSearch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientSearch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->searchResultsChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientSearch::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSearch::searchResultsChanged)) {
                *result = 0;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< drinq::data::StringDecorator* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ClientSearch *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< drinq::data::StringDecorator**>(_v) = _t->searchText(); break;
        case 1: *reinterpret_cast< QQmlListProperty<drinq::models::Client>*>(_v) = _t->ui_searchResults(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject drinq::models::ClientSearch::staticMetaObject = { {
    &data::Entity::staticMetaObject,
    qt_meta_stringdata_drinq__models__ClientSearch.data,
    qt_meta_data_drinq__models__ClientSearch,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *drinq::models::ClientSearch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *drinq::models::ClientSearch::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_drinq__models__ClientSearch.stringdata0))
        return static_cast<void*>(this);
    return data::Entity::qt_metacast(_clname);
}

int drinq::models::ClientSearch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = data::Entity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void drinq::models::ClientSearch::searchResultsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
