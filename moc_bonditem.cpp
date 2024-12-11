/****************************************************************************
** Meta object code from reading C++ file 'bonditem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bonditem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bonditem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BondItem_t {
    QByteArrayData data[14];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BondItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BondItem_t qt_meta_stringdata_BondItem = {
    {
QT_MOC_LITERAL(0, 0, 8), // "BondItem"
QT_MOC_LITERAL(1, 9, 12), // "bondSelected"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "BondItem*"
QT_MOC_LITERAL(4, 33, 14), // "bondUnselected"
QT_MOC_LITERAL(5, 48, 12), // "setSelection"
QT_MOC_LITERAL(6, 61, 8), // "selected"
QT_MOC_LITERAL(7, 70, 15), // "toggleSelection"
QT_MOC_LITERAL(8, 86, 10), // "emitSignal"
QT_MOC_LITERAL(9, 97, 10), // "selectBond"
QT_MOC_LITERAL(10, 108, 12), // "unselectBond"
QT_MOC_LITERAL(11, 121, 13), // "setDoubleBond"
QT_MOC_LITERAL(12, 135, 2), // "on"
QT_MOC_LITERAL(13, 138, 16) // "updateAppearence"

    },
    "BondItem\0bondSelected\0\0BondItem*\0"
    "bondUnselected\0setSelection\0selected\0"
    "toggleSelection\0emitSignal\0selectBond\0"
    "unselectBond\0setDoubleBond\0on\0"
    "updateAppearence"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BondItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   75,    2, 0x0a /* Public */,
       7,    1,   78,    2, 0x0a /* Public */,
       7,    0,   81,    2, 0x2a /* Public | MethodCloned */,
       9,    1,   82,    2, 0x0a /* Public */,
       9,    0,   85,    2, 0x2a /* Public | MethodCloned */,
      10,    1,   86,    2, 0x0a /* Public */,
      10,    0,   89,    2, 0x2a /* Public | MethodCloned */,
      11,    1,   90,    2, 0x0a /* Public */,
      13,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,

       0        // eod
};

void BondItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BondItem *_t = static_cast<BondItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->bondSelected((*reinterpret_cast< BondItem*(*)>(_a[1]))); break;
        case 1: _t->bondUnselected((*reinterpret_cast< BondItem*(*)>(_a[1]))); break;
        case 2: _t->setSelection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->toggleSelection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->toggleSelection(); break;
        case 5: _t->selectBond((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->selectBond(); break;
        case 7: _t->unselectBond((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->unselectBond(); break;
        case 9: _t->setDoubleBond((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->updateAppearence(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BondItem* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BondItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BondItem::*_t)(BondItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BondItem::bondSelected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BondItem::*_t)(BondItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BondItem::bondUnselected)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject BondItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BondItem.data,
      qt_meta_data_BondItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BondItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BondItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BondItem.stringdata0))
        return static_cast<void*>(const_cast< BondItem*>(this));
    if (!strcmp(_clname, "QGraphicsLineItem"))
        return static_cast< QGraphicsLineItem*>(const_cast< BondItem*>(this));
    return QObject::qt_metacast(_clname);
}

int BondItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void BondItem::bondSelected(BondItem * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BondItem::bondUnselected(BondItem * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
