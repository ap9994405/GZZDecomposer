/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "tabPageChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "index"
QT_MOC_LITERAL(4, 33, 8), // "clearAll"
QT_MOC_LITERAL(5, 42, 11), // "saveClicked"
QT_MOC_LITERAL(6, 54, 10), // "showZZInfo"
QT_MOC_LITERAL(7, 65, 9), // "showAbout"
QT_MOC_LITERAL(8, 75, 11), // "showAboutQt"
QT_MOC_LITERAL(9, 87, 4), // "undo"
QT_MOC_LITERAL(10, 92, 4), // "redo"
QT_MOC_LITERAL(11, 97, 26), // "processZZPolynomialRequest"
QT_MOC_LITERAL(12, 124, 11), // "GraphModel*"
QT_MOC_LITERAL(13, 136, 5), // "model"
QT_MOC_LITERAL(14, 142, 33), // "builderProcessZZPolynomialReq..."
QT_MOC_LITERAL(15, 176, 13), // "setGridRotate"
QT_MOC_LITERAL(16, 190, 6), // "rotate"
QT_MOC_LITERAL(17, 197, 23), // "toggleSeparateFragments"
QT_MOC_LITERAL(18, 221, 11), // "isSeparated"
QT_MOC_LITERAL(19, 233, 4), // "test"
QT_MOC_LITERAL(20, 238, 10) // "screenshot"

    },
    "MainWindow\0tabPageChanged\0\0index\0"
    "clearAll\0saveClicked\0showZZInfo\0"
    "showAbout\0showAboutQt\0undo\0redo\0"
    "processZZPolynomialRequest\0GraphModel*\0"
    "model\0builderProcessZZPolynomialRequest\0"
    "setGridRotate\0rotate\0toggleSeparateFragments\0"
    "isSeparated\0test\0screenshot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       4,    0,   87,    2, 0x08 /* Private */,
       5,    0,   88,    2, 0x08 /* Private */,
       6,    0,   89,    2, 0x08 /* Private */,
       7,    0,   90,    2, 0x08 /* Private */,
       8,    0,   91,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    1,   94,    2, 0x08 /* Private */,
      14,    1,   97,    2, 0x08 /* Private */,
      15,    1,  100,    2, 0x08 /* Private */,
      17,    1,  103,    2, 0x08 /* Private */,
      19,    0,  106,    2, 0x08 /* Private */,
      20,    0,  107,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tabPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->clearAll(); break;
        case 2: _t->saveClicked(); break;
        case 3: _t->showZZInfo(); break;
        case 4: _t->showAbout(); break;
        case 5: _t->showAboutQt(); break;
        case 6: _t->undo(); break;
        case 7: _t->redo(); break;
        case 8: _t->processZZPolynomialRequest((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 9: _t->builderProcessZZPolynomialRequest((*reinterpret_cast< GraphModel*(*)>(_a[1]))); break;
        case 10: _t->setGridRotate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->toggleSeparateFragments((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->test(); break;
        case 13: _t->screenshot(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
