/****************************************************************************
** Meta object code from reading C++ file 'gzzcalculatorjob.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gzzcalculatorjob.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gzzcalculatorjob.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GZZCalculatorJob_t {
    QByteArrayData data[10];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GZZCalculatorJob_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GZZCalculatorJob_t qt_meta_stringdata_GZZCalculatorJob = {
    {
QT_MOC_LITERAL(0, 0, 16), // "GZZCalculatorJob"
QT_MOC_LITERAL(1, 17, 7), // "removed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 17), // "GZZCalculatorJob*"
QT_MOC_LITERAL(4, 44, 3), // "job"
QT_MOC_LITERAL(5, 48, 7), // "updated"
QT_MOC_LITERAL(6, 56, 5), // "start"
QT_MOC_LITERAL(7, 62, 13), // "cancelClicked"
QT_MOC_LITERAL(8, 76, 12), // "startClicked"
QT_MOC_LITERAL(9, 89, 12) // "calcFinished"

    },
    "GZZCalculatorJob\0removed\0\0GZZCalculatorJob*\0"
    "job\0updated\0start\0cancelClicked\0"
    "startClicked\0calcFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GZZCalculatorJob[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x08 /* Private */,
       8,    0,   52,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GZZCalculatorJob::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GZZCalculatorJob *_t = static_cast<GZZCalculatorJob *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->removed((*reinterpret_cast< GZZCalculatorJob*(*)>(_a[1]))); break;
        case 1: _t->updated((*reinterpret_cast< GZZCalculatorJob*(*)>(_a[1]))); break;
        case 2: _t->start(); break;
        case 3: _t->cancelClicked(); break;
        case 4: _t->startClicked(); break;
        case 5: _t->calcFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GZZCalculatorJob* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GZZCalculatorJob* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GZZCalculatorJob::*_t)(GZZCalculatorJob * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GZZCalculatorJob::removed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GZZCalculatorJob::*_t)(GZZCalculatorJob * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GZZCalculatorJob::updated)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GZZCalculatorJob::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GZZCalculatorJob.data,
      qt_meta_data_GZZCalculatorJob,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GZZCalculatorJob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GZZCalculatorJob::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GZZCalculatorJob.stringdata0))
        return static_cast<void*>(const_cast< GZZCalculatorJob*>(this));
    return QObject::qt_metacast(_clname);
}

int GZZCalculatorJob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void GZZCalculatorJob::removed(GZZCalculatorJob * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GZZCalculatorJob::updated(GZZCalculatorJob * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
