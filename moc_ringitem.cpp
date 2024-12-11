/****************************************************************************
** Meta object code from reading C++ file 'ringitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ringitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ringitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RingItem_t {
    QByteArrayData data[13];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RingItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RingItem_t qt_meta_stringdata_RingItem = {
    {
QT_MOC_LITERAL(0, 0, 8), // "RingItem"
QT_MOC_LITERAL(1, 9, 7), // "clicked"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 9), // "RingItem*"
QT_MOC_LITERAL(4, 28, 11), // "addBondItem"
QT_MOC_LITERAL(5, 40, 9), // "BondItem*"
QT_MOC_LITERAL(6, 50, 16), // "UnselectAllBonds"
QT_MOC_LITERAL(7, 67, 14), // "SelectAllBonds"
QT_MOC_LITERAL(8, 82, 10), // "hoverEnter"
QT_MOC_LITERAL(9, 93, 10), // "hoverLeave"
QT_MOC_LITERAL(10, 104, 8), // "getCoord"
QT_MOC_LITERAL(11, 113, 6), // "notify"
QT_MOC_LITERAL(12, 120, 13) // "getNumOfBonds"

    },
    "RingItem\0clicked\0\0RingItem*\0addBondItem\0"
    "BondItem*\0UnselectAllBonds\0SelectAllBonds\0"
    "hoverEnter\0hoverLeave\0getCoord\0notify\0"
    "getNumOfBonds"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RingItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   62,    2, 0x0a /* Public */,
       6,    0,   65,    2, 0x0a /* Public */,
       7,    0,   66,    2, 0x0a /* Public */,
       8,    0,   67,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QPoint,
    QMetaType::Void,
    QMetaType::Int,

       0        // eod
};

void RingItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RingItem *_t = static_cast<RingItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< RingItem*(*)>(_a[1]))); break;
        case 1: _t->addBondItem((*reinterpret_cast< BondItem*(*)>(_a[1]))); break;
        case 2: _t->UnselectAllBonds(); break;
        case 3: _t->SelectAllBonds(); break;
        case 4: _t->hoverEnter(); break;
        case 5: _t->hoverLeave(); break;
        case 6: { QPoint _r = _t->getCoord();
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = _r; }  break;
        case 7: _t->notify(); break;
        case 8: { int _r = _t->getNumOfBonds();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RingItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RingItem::*_t)(RingItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RingItem::clicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject RingItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RingItem.data,
      qt_meta_data_RingItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RingItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RingItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RingItem.stringdata0))
        return static_cast<void*>(const_cast< RingItem*>(this));
    if (!strcmp(_clname, "QGraphicsPolygonItem"))
        return static_cast< QGraphicsPolygonItem*>(const_cast< RingItem*>(this));
    return QObject::qt_metacast(_clname);
}

int RingItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void RingItem::clicked(RingItem * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
