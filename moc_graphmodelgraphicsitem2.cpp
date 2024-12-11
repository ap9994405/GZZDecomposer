/****************************************************************************
** Meta object code from reading C++ file 'graphmodelgraphicsitem2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphmodelgraphicsitem2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphmodelgraphicsitem2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GraphModelGraphicsItem2_t {
    QByteArrayData data[10];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphModelGraphicsItem2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphModelGraphicsItem2_t qt_meta_stringdata_GraphModelGraphicsItem2 = {
    {
QT_MOC_LITERAL(0, 0, 23), // "GraphModelGraphicsItem2"
QT_MOC_LITERAL(1, 24, 19), // "ZZPolynomialRequest"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 11), // "GraphModel*"
QT_MOC_LITERAL(4, 57, 5), // "model"
QT_MOC_LITERAL(5, 63, 16), // "itemBondSelected"
QT_MOC_LITERAL(6, 80, 9), // "BondItem*"
QT_MOC_LITERAL(7, 90, 4), // "bond"
QT_MOC_LITERAL(8, 95, 18), // "itemBondUnselected"
QT_MOC_LITERAL(9, 114, 21) // "itemPolynomialChanged"

    },
    "GraphModelGraphicsItem2\0ZZPolynomialRequest\0"
    "\0GraphModel*\0model\0itemBondSelected\0"
    "BondItem*\0bond\0itemBondUnselected\0"
    "itemPolynomialChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphModelGraphicsItem2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x08 /* Private */,
       8,    1,   40,    2, 0x08 /* Private */,
       9,    1,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void GraphModelGraphicsItem2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphModelGraphicsItem2 *_t = static_cast<GraphModelGraphicsItem2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZZPolynomialRequest((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 1: _t->itemBondSelected((*reinterpret_cast< BondItem*(*)>(_a[1]))); break;
        case 2: _t->itemBondUnselected((*reinterpret_cast< BondItem*(*)>(_a[1]))); break;
        case 3: _t->itemPolynomialChanged((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GraphModelGraphicsItem2::*_t)(GraphModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphModelGraphicsItem2::ZZPolynomialRequest)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject GraphModelGraphicsItem2::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GraphModelGraphicsItem2.data,
      qt_meta_data_GraphModelGraphicsItem2,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GraphModelGraphicsItem2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphModelGraphicsItem2::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GraphModelGraphicsItem2.stringdata0))
        return static_cast<void*>(const_cast< GraphModelGraphicsItem2*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< GraphModelGraphicsItem2*>(this));
    return QObject::qt_metacast(_clname);
}

int GraphModelGraphicsItem2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GraphModelGraphicsItem2::ZZPolynomialRequest(GraphModel * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
