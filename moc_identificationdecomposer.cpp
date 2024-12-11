/****************************************************************************
** Meta object code from reading C++ file 'identificationdecomposer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "identificationdecomposer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'identificationdecomposer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IdentificationDecomposer_t {
    QByteArrayData data[22];
    char stringdata0[303];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IdentificationDecomposer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IdentificationDecomposer_t qt_meta_stringdata_IdentificationDecomposer = {
    {
QT_MOC_LITERAL(0, 0, 24), // "IdentificationDecomposer"
QT_MOC_LITERAL(1, 25, 19), // "ZZPolynomialRequest"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 11), // "GraphModel*"
QT_MOC_LITERAL(4, 58, 5), // "model"
QT_MOC_LITERAL(5, 64, 5), // "clear"
QT_MOC_LITERAL(6, 70, 15), // "getZZPolynomial"
QT_MOC_LITERAL(7, 86, 4), // "undo"
QT_MOC_LITERAL(8, 91, 4), // "redo"
QT_MOC_LITERAL(9, 96, 9), // "exportSVG"
QT_MOC_LITERAL(10, 106, 19), // "unidentItemSelected"
QT_MOC_LITERAL(11, 126, 5), // "index"
QT_MOC_LITERAL(12, 132, 22), // "identItemDoubleClicked"
QT_MOC_LITERAL(13, 155, 21), // "IdentifyButtonClicked"
QT_MOC_LITERAL(14, 177, 23), // "UnidentifyButtonClicked"
QT_MOC_LITERAL(15, 201, 15), // "identRightClick"
QT_MOC_LITERAL(16, 217, 5), // "point"
QT_MOC_LITERAL(17, 223, 17), // "unidentRightClick"
QT_MOC_LITERAL(18, 241, 18), // "confirmCombination"
QT_MOC_LITERAL(19, 260, 10), // "QListView*"
QT_MOC_LITERAL(20, 271, 6), // "target"
QT_MOC_LITERAL(21, 278, 24) // "childZZPolynomialRequest"

    },
    "IdentificationDecomposer\0ZZPolynomialRequest\0"
    "\0GraphModel*\0model\0clear\0getZZPolynomial\0"
    "undo\0redo\0exportSVG\0unidentItemSelected\0"
    "index\0identItemDoubleClicked\0"
    "IdentifyButtonClicked\0UnidentifyButtonClicked\0"
    "identRightClick\0point\0unidentRightClick\0"
    "confirmCombination\0QListView*\0target\0"
    "childZZPolynomialRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IdentificationDecomposer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    0,   89,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    0,   91,    2, 0x0a /* Public */,
      10,    1,   92,    2, 0x08 /* Private */,
      12,    1,   95,    2, 0x08 /* Private */,
      13,    0,   98,    2, 0x08 /* Private */,
      14,    0,   99,    2, 0x08 /* Private */,
      15,    1,  100,    2, 0x08 /* Private */,
      17,    1,  103,    2, 0x08 /* Private */,
      18,    2,  106,    2, 0x08 /* Private */,
      21,    1,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   11,
    QMetaType::Void, QMetaType::QModelIndex,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   16,
    QMetaType::Void, QMetaType::QPoint,   16,
    QMetaType::Void, 0x80000000 | 19, QMetaType::QPoint,   20,   16,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void IdentificationDecomposer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IdentificationDecomposer *_t = static_cast<IdentificationDecomposer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZZPolynomialRequest((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 1: _t->clear(); break;
        case 2: { QString _r = _t->getZZPolynomial();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: _t->undo(); break;
        case 4: _t->redo(); break;
        case 5: _t->exportSVG(); break;
        case 6: _t->unidentItemSelected((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 7: _t->identItemDoubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 8: _t->IdentifyButtonClicked(); break;
        case 9: _t->UnidentifyButtonClicked(); break;
        case 10: _t->identRightClick((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 11: _t->unidentRightClick((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 12: _t->confirmCombination((*reinterpret_cast< QListView*(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 13: _t->childZZPolynomialRequest((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QListView* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (IdentificationDecomposer::*_t)(GraphModel * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&IdentificationDecomposer::ZZPolynomialRequest)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject IdentificationDecomposer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_IdentificationDecomposer.data,
      qt_meta_data_IdentificationDecomposer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *IdentificationDecomposer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IdentificationDecomposer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_IdentificationDecomposer.stringdata0))
        return static_cast<void*>(const_cast< IdentificationDecomposer*>(this));
    return QWidget::qt_metacast(_clname);
}

int IdentificationDecomposer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void IdentificationDecomposer::ZZPolynomialRequest(GraphModel * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
