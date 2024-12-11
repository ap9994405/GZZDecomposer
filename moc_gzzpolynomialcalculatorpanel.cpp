/****************************************************************************
** Meta object code from reading C++ file 'gzzpolynomialcalculatorpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gzzpolynomialcalculatorpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gzzpolynomialcalculatorpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_porsche_t {
    QByteArrayData data[10];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_porsche_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_porsche_t qt_meta_stringdata_porsche = {
    {
QT_MOC_LITERAL(0, 0, 7), // "porsche"
QT_MOC_LITERAL(1, 8, 6), // "addRow"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 11), // "GraphModel*"
QT_MOC_LITERAL(4, 28, 5), // "model"
QT_MOC_LITERAL(5, 34, 12), // "addRowAndRun"
QT_MOC_LITERAL(6, 47, 10), // "jobRemoved"
QT_MOC_LITERAL(7, 58, 17), // "GZZCalculatorJob*"
QT_MOC_LITERAL(8, 76, 3), // "job"
QT_MOC_LITERAL(9, 80, 10) // "jobUpdated"

    },
    "porsche\0addRow\0\0GraphModel*\0model\0"
    "addRowAndRun\0jobRemoved\0GZZCalculatorJob*\0"
    "job\0jobUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_porsche[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x08 /* Private */,
       9,    1,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void porsche::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        porsche *_t = static_cast<porsche *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addRow((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 1: _t->addRowAndRun((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 2: _t->jobRemoved((*reinterpret_cast< GZZCalculatorJob*(*)>(_a[1]))); break;
        case 3: _t->jobUpdated((*reinterpret_cast< GZZCalculatorJob*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject porsche::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_porsche.data,
      qt_meta_data_porsche,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *porsche::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *porsche::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_porsche.stringdata0))
        return static_cast<void*>(const_cast< porsche*>(this));
    return QWidget::qt_metacast(_clname);
}

int porsche::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
