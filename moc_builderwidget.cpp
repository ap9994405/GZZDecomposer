/****************************************************************************
** Meta object code from reading C++ file 'builderwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "builderwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'builderwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BuilderWidget_t {
    QByteArrayData data[20];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BuilderWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BuilderWidget_t qt_meta_stringdata_BuilderWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "BuilderWidget"
QT_MOC_LITERAL(1, 14, 8), // "modified"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 19), // "ZZPolynomialRequest"
QT_MOC_LITERAL(4, 44, 11), // "GraphModel*"
QT_MOC_LITERAL(5, 56, 10), // "selectBond"
QT_MOC_LITERAL(6, 67, 9), // "BondItem*"
QT_MOC_LITERAL(7, 77, 12), // "unselectBond"
QT_MOC_LITERAL(8, 90, 11), // "ringClicked"
QT_MOC_LITERAL(9, 102, 9), // "RingItem*"
QT_MOC_LITERAL(10, 112, 4), // "ring"
QT_MOC_LITERAL(11, 117, 11), // "contextMenu"
QT_MOC_LITERAL(12, 129, 5), // "point"
QT_MOC_LITERAL(13, 135, 5), // "clear"
QT_MOC_LITERAL(14, 141, 9), // "draw_grid"
QT_MOC_LITERAL(15, 151, 8), // "getGraph"
QT_MOC_LITERAL(16, 160, 16), // "QList<EdgeModel>"
QT_MOC_LITERAL(17, 177, 13), // "getGraphModel"
QT_MOC_LITERAL(18, 191, 13), // "setGridRotate"
QT_MOC_LITERAL(19, 205, 6) // "rotate"

    },
    "BuilderWidget\0modified\0\0ZZPolynomialRequest\0"
    "GraphModel*\0selectBond\0BondItem*\0"
    "unselectBond\0ringClicked\0RingItem*\0"
    "ring\0contextMenu\0point\0clear\0draw_grid\0"
    "getGraph\0QList<EdgeModel>\0getGraphModel\0"
    "setGridRotate\0rotate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BuilderWidget[] = {

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
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   73,    2, 0x08 /* Private */,
       7,    1,   76,    2, 0x08 /* Private */,
       8,    1,   79,    2, 0x08 /* Private */,
      11,    1,   82,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x0a /* Public */,
      14,    0,   86,    2, 0x0a /* Public */,
      15,    0,   87,    2, 0x0a /* Public */,
      17,    0,   88,    2, 0x0a /* Public */,
      18,    1,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QPoint,   12,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 16,
    0x80000000 | 4,
    QMetaType::Void, QMetaType::Bool,   19,

       0        // eod
};

void BuilderWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BuilderWidget *_t = static_cast<BuilderWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->modified(); break;
        case 1: _t->ZZPolynomialRequest((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 2: _t->selectBond((*reinterpret_cast< BondItem*(*)>(_a[1]))); break;
        case 3: _t->unselectBond((*reinterpret_cast< BondItem*(*)>(_a[1]))); break;
        case 4: _t->ringClicked((*reinterpret_cast< RingItem*(*)>(_a[1]))); break;
        case 5: _t->contextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 6: _t->clear(); break;
        case 7: _t->draw_grid(); break;
        case 8: { QList<EdgeModel> _r = _t->getGraph();
            if (_a[0]) *reinterpret_cast< QList<EdgeModel>*>(_a[0]) = _r; }  break;
        case 9: { GraphModel* _r = _t->getGraphModel();
            if (_a[0]) *reinterpret_cast< GraphModel**>(_a[0]) = _r; }  break;
        case 10: _t->setGridRotate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BondItem* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< BondItem* >(); break;
            }
            break;
        case 4:
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
            typedef void (BuilderWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BuilderWidget::modified)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BuilderWidget::*_t)(GraphModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BuilderWidget::ZZPolynomialRequest)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject BuilderWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BuilderWidget.data,
      qt_meta_data_BuilderWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BuilderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BuilderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BuilderWidget.stringdata0))
        return static_cast<void*>(const_cast< BuilderWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int BuilderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void BuilderWidget::modified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void BuilderWidget::ZZPolynomialRequest(GraphModel * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
