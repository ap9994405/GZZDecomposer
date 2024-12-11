/****************************************************************************
** Meta object code from reading C++ file 'graphmodelgraphicsitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphmodelgraphicsitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphmodelgraphicsitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GraphModelGraphicsItem_t {
    QByteArrayData data[18];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphModelGraphicsItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphModelGraphicsItem_t qt_meta_stringdata_GraphModelGraphicsItem = {
    {
QT_MOC_LITERAL(0, 0, 22), // "GraphModelGraphicsItem"
QT_MOC_LITERAL(1, 23, 19), // "ZZPolynomialRequest"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 11), // "GraphModel*"
QT_MOC_LITERAL(4, 56, 5), // "model"
QT_MOC_LITERAL(5, 62, 10), // "tagChanged"
QT_MOC_LITERAL(6, 73, 16), // "itemBondSelected"
QT_MOC_LITERAL(7, 90, 9), // "BondItem*"
QT_MOC_LITERAL(8, 100, 4), // "bond"
QT_MOC_LITERAL(9, 105, 18), // "itemBondUnselected"
QT_MOC_LITERAL(10, 124, 21), // "itemPolynomialChanged"
QT_MOC_LITERAL(11, 146, 16), // "itemStateChanged"
QT_MOC_LITERAL(12, 163, 15), // "childTagChanged"
QT_MOC_LITERAL(13, 179, 14), // "setGridRotated"
QT_MOC_LITERAL(14, 194, 6), // "rotate"
QT_MOC_LITERAL(15, 201, 13), // "isGridRotated"
QT_MOC_LITERAL(16, 215, 5), // "reset"
QT_MOC_LITERAL(17, 221, 18) // "updateBoundingRect"

    },
    "GraphModelGraphicsItem\0ZZPolynomialRequest\0"
    "\0GraphModel*\0model\0tagChanged\0"
    "itemBondSelected\0BondItem*\0bond\0"
    "itemBondUnselected\0itemPolynomialChanged\0"
    "itemStateChanged\0childTagChanged\0"
    "setGridRotated\0rotate\0isGridRotated\0"
    "reset\0updateBoundingRect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphModelGraphicsItem[] = {

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
       5,    0,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   73,    2, 0x08 /* Private */,
       9,    1,   76,    2, 0x08 /* Private */,
      10,    1,   79,    2, 0x08 /* Private */,
      11,    1,   82,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    1,   86,    2, 0x0a /* Public */,
      15,    0,   89,    2, 0x0a /* Public */,
      16,    0,   90,    2, 0x0a /* Public */,
      17,    0,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GraphModelGraphicsItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphModelGraphicsItem *_t = static_cast<GraphModelGraphicsItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZZPolynomialRequest((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 1: _t->tagChanged(); break;
        case 2: _t->itemBondSelected((*reinterpret_cast< BondItem*(*)>(_a[1]))); break;
        case 3: _t->itemBondUnselected((*reinterpret_cast< BondItem*(*)>(_a[1]))); break;
        case 4: _t->itemPolynomialChanged((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 5: _t->itemStateChanged((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 6: _t->childTagChanged(); break;
        case 7: _t->setGridRotated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: { bool _r = _t->isGridRotated();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: _t->reset(); break;
        case 10: _t->updateBoundingRect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GraphModelGraphicsItem::*_t)(GraphModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphModelGraphicsItem::ZZPolynomialRequest)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GraphModelGraphicsItem::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphModelGraphicsItem::tagChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GraphModelGraphicsItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GraphModelGraphicsItem.data,
      qt_meta_data_GraphModelGraphicsItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GraphModelGraphicsItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphModelGraphicsItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GraphModelGraphicsItem.stringdata0))
        return static_cast<void*>(const_cast< GraphModelGraphicsItem*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< GraphModelGraphicsItem*>(this));
    return QObject::qt_metacast(_clname);
}

int GraphModelGraphicsItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void GraphModelGraphicsItem::ZZPolynomialRequest(GraphModel * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphModelGraphicsItem::tagChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
