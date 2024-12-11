/****************************************************************************
** Meta object code from reading C++ file 'graphmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GraphModel_t {
    QByteArrayData data[28];
    char stringdata0[349];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphModel_t qt_meta_stringdata_GraphModel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GraphModel"
QT_MOC_LITERAL(1, 11, 16), // "SelectionChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "GraphModel*"
QT_MOC_LITERAL(4, 41, 5), // "model"
QT_MOC_LITERAL(5, 47, 12), // "Disconnected"
QT_MOC_LITERAL(6, 60, 12), // "StateChanged"
QT_MOC_LITERAL(7, 73, 17), // "PolynomialChanged"
QT_MOC_LITERAL(8, 91, 10), // "TagChanged"
QT_MOC_LITERAL(9, 102, 12), // "getDaughters"
QT_MOC_LITERAL(10, 115, 18), // "QList<GraphModel*>"
QT_MOC_LITERAL(11, 134, 9), // "EdgeModel"
QT_MOC_LITERAL(12, 144, 4), // "edge"
QT_MOC_LITERAL(13, 149, 10), // "selectBond"
QT_MOC_LITERAL(14, 160, 12), // "unselectBond"
QT_MOC_LITERAL(15, 173, 14), // "isBondSelected"
QT_MOC_LITERAL(16, 188, 15), // "getSelectedBond"
QT_MOC_LITERAL(17, 204, 12), // "getFragments"
QT_MOC_LITERAL(18, 217, 10), // "getZZInput"
QT_MOC_LITERAL(19, 228, 11), // "connections"
QT_MOC_LITERAL(20, 240, 9), // "hydrogens"
QT_MOC_LITERAL(21, 250, 7), // "setDead"
QT_MOC_LITERAL(22, 258, 6), // "isDead"
QT_MOC_LITERAL(23, 265, 7), // "prepare"
QT_MOC_LITERAL(24, 273, 17), // "getNoBondDaughter"
QT_MOC_LITERAL(25, 291, 18), // "getNoAtomsDaughter"
QT_MOC_LITERAL(26, 310, 17), // "getNoRingDaughter"
QT_MOC_LITERAL(27, 328, 20) // "getNoBisRingDaughter"

    },
    "GraphModel\0SelectionChanged\0\0GraphModel*\0"
    "model\0Disconnected\0StateChanged\0"
    "PolynomialChanged\0TagChanged\0getDaughters\0"
    "QList<GraphModel*>\0EdgeModel\0edge\0"
    "selectBond\0unselectBond\0isBondSelected\0"
    "getSelectedBond\0getFragments\0getZZInput\0"
    "connections\0hydrogens\0setDead\0isDead\0"
    "prepare\0getNoBondDaughter\0getNoAtomsDaughter\0"
    "getNoRingDaughter\0getNoBisRingDaughter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,
       5,    1,  107,    2, 0x06 /* Public */,
       6,    1,  110,    2, 0x06 /* Public */,
       7,    1,  113,    2, 0x06 /* Public */,
       8,    1,  116,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  119,    2, 0x0a /* Public */,
      13,    1,  122,    2, 0x0a /* Public */,
      14,    0,  125,    2, 0x0a /* Public */,
      15,    0,  126,    2, 0x0a /* Public */,
      16,    0,  127,    2, 0x0a /* Public */,
      17,    0,  128,    2, 0x0a /* Public */,
      18,    2,  129,    2, 0x0a /* Public */,
      21,    1,  134,    2, 0x0a /* Public */,
      23,    0,  137,    2, 0x0a /* Public */,
      24,    1,  138,    2, 0x08 /* Private */,
      25,    1,  141,    2, 0x08 /* Private */,
      26,    1,  144,    2, 0x08 /* Private */,
      27,    1,  147,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    0x80000000 | 10, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Bool,
    0x80000000 | 11,
    0x80000000 | 10,
    QMetaType::QString, QMetaType::Bool, QMetaType::Bool,   19,   20,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    0x80000000 | 3, 0x80000000 | 11,   12,
    0x80000000 | 3, 0x80000000 | 11,   12,
    0x80000000 | 10, 0x80000000 | 11,   12,
    0x80000000 | 10, 0x80000000 | 11,   12,

       0        // eod
};

void GraphModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphModel *_t = static_cast<GraphModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SelectionChanged((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 1: _t->Disconnected((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 2: _t->StateChanged((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 3: _t->PolynomialChanged((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 4: _t->TagChanged((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 5: { QList<GraphModel*> _r = _t->getDaughters((*reinterpret_cast< EdgeModel(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<GraphModel*>*>(_a[0]) = _r; }  break;
        case 6: _t->selectBond((*reinterpret_cast< EdgeModel(*)>(_a[1]))); break;
        case 7: _t->unselectBond(); break;
        case 8: { bool _r = _t->isBondSelected();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { EdgeModel _r = _t->getSelectedBond();
            if (_a[0]) *reinterpret_cast< EdgeModel*>(_a[0]) = _r; }  break;
        case 10: { QList<GraphModel*> _r = _t->getFragments();
            if (_a[0]) *reinterpret_cast< QList<GraphModel*>*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->getZZInput((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: _t->setDead((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->prepare(); break;
        case 14: { GraphModel* _r = _t->getNoBondDaughter((*reinterpret_cast< EdgeModel(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< GraphModel**>(_a[0]) = _r; }  break;
        case 15: { GraphModel* _r = _t->getNoAtomsDaughter((*reinterpret_cast< EdgeModel(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< GraphModel**>(_a[0]) = _r; }  break;
        case 16: { QList<GraphModel*> _r = _t->getNoRingDaughter((*reinterpret_cast< EdgeModel(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<GraphModel*>*>(_a[0]) = _r; }  break;
        case 17: { QList<GraphModel*> _r = _t->getNoBisRingDaughter((*reinterpret_cast< EdgeModel(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<GraphModel*>*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GraphModel* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GraphModel* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GraphModel* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GraphModel* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GraphModel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GraphModel::*_t)(GraphModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphModel::SelectionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GraphModel::*_t)(GraphModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphModel::Disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GraphModel::*_t)(GraphModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphModel::StateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GraphModel::*_t)(GraphModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphModel::PolynomialChanged)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (GraphModel::*_t)(GraphModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphModel::TagChanged)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject GraphModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GraphModel.data,
      qt_meta_data_GraphModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GraphModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GraphModel.stringdata0))
        return static_cast<void*>(const_cast< GraphModel*>(this));
    return QObject::qt_metacast(_clname);
}

int GraphModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void GraphModel::SelectionChanged(GraphModel * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphModel::Disconnected(GraphModel * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GraphModel::StateChanged(GraphModel * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GraphModel::PolynomialChanged(GraphModel * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GraphModel::TagChanged(GraphModel * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
