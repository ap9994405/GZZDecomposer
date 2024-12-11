/****************************************************************************
** Meta object code from reading C++ file 'graphicsitemdebugdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphicsitemdebugdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicsitemdebugdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GraphicsItemDebugDialog_t {
    QByteArrayData data[8];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicsItemDebugDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicsItemDebugDialog_t qt_meta_stringdata_GraphicsItemDebugDialog = {
    {
QT_MOC_LITERAL(0, 0, 23), // "GraphicsItemDebugDialog"
QT_MOC_LITERAL(1, 24, 14), // "loadProperties"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 13), // "update_rect_x"
QT_MOC_LITERAL(4, 54, 5), // "value"
QT_MOC_LITERAL(5, 60, 13), // "update_rect_y"
QT_MOC_LITERAL(6, 74, 13), // "update_rect_w"
QT_MOC_LITERAL(7, 88, 13) // "update_rect_h"

    },
    "GraphicsItemDebugDialog\0loadProperties\0"
    "\0update_rect_x\0value\0update_rect_y\0"
    "update_rect_w\0update_rect_h"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsItemDebugDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       6,    1,   46,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void GraphicsItemDebugDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphicsItemDebugDialog *_t = static_cast<GraphicsItemDebugDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadProperties(); break;
        case 1: _t->update_rect_x((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->update_rect_y((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->update_rect_w((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->update_rect_h((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GraphicsItemDebugDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GraphicsItemDebugDialog.data,
      qt_meta_data_GraphicsItemDebugDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GraphicsItemDebugDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsItemDebugDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsItemDebugDialog.stringdata0))
        return static_cast<void*>(const_cast< GraphicsItemDebugDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int GraphicsItemDebugDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
