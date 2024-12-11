/****************************************************************************
** Meta object code from reading C++ file 'zzpolynomialcalculatorpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "zzpolynomialcalculatorpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'zzpolynomialcalculatorpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZZPolynomialCalculatorPanel_t {
    QByteArrayData data[10];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZZPolynomialCalculatorPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZZPolynomialCalculatorPanel_t qt_meta_stringdata_ZZPolynomialCalculatorPanel = {
    {
QT_MOC_LITERAL(0, 0, 27), // "ZZPolynomialCalculatorPanel"
QT_MOC_LITERAL(1, 28, 6), // "addRow"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "GraphModel*"
QT_MOC_LITERAL(4, 48, 5), // "model"
QT_MOC_LITERAL(5, 54, 12), // "addRowAndRun"
QT_MOC_LITERAL(6, 67, 10), // "jobRemoved"
QT_MOC_LITERAL(7, 78, 16), // "ZZCalculatorJob*"
QT_MOC_LITERAL(8, 95, 3), // "job"
QT_MOC_LITERAL(9, 99, 10) // "jobUpdated"

    },
    "ZZPolynomialCalculatorPanel\0addRow\0\0"
    "GraphModel*\0model\0addRowAndRun\0"
    "jobRemoved\0ZZCalculatorJob*\0job\0"
    "jobUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZZPolynomialCalculatorPanel[] = {

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

void ZZPolynomialCalculatorPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZZPolynomialCalculatorPanel *_t = static_cast<ZZPolynomialCalculatorPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addRow((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 1: _t->addRowAndRun((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 2: _t->jobRemoved((*reinterpret_cast< ZZCalculatorJob*(*)>(_a[1]))); break;
        case 3: _t->jobUpdated((*reinterpret_cast< ZZCalculatorJob*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ZZPolynomialCalculatorPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ZZPolynomialCalculatorPanel.data,
      qt_meta_data_ZZPolynomialCalculatorPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZZPolynomialCalculatorPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZZPolynomialCalculatorPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZZPolynomialCalculatorPanel.stringdata0))
        return static_cast<void*>(const_cast< ZZPolynomialCalculatorPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int ZZPolynomialCalculatorPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
