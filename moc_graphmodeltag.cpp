/****************************************************************************
** Meta object code from reading C++ file 'graphmodeltag.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "graphmodeltag.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphmodeltag.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GraphModelTag_t {
    QByteArrayData data[13];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphModelTag_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphModelTag_t qt_meta_stringdata_GraphModelTag = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GraphModelTag"
QT_MOC_LITERAL(1, 14, 10), // "tagChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "setFont"
QT_MOC_LITERAL(4, 34, 4), // "font"
QT_MOC_LITERAL(5, 39, 7), // "setText"
QT_MOC_LITERAL(6, 47, 4), // "text"
QT_MOC_LITERAL(7, 52, 4), // "html"
QT_MOC_LITERAL(8, 57, 13), // "finishEditing"
QT_MOC_LITERAL(9, 71, 12), // "textChanging"
QT_MOC_LITERAL(10, 84, 21), // "adjustEditBoxPosition"
QT_MOC_LITERAL(11, 106, 6), // "setTag"
QT_MOC_LITERAL(12, 113, 3) // "tag"

    },
    "GraphModelTag\0tagChanged\0\0setFont\0"
    "font\0setText\0text\0html\0finishEditing\0"
    "textChanging\0adjustEditBoxPosition\0"
    "setTag\0tag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphModelTag[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   55,    2, 0x0a /* Public */,
       5,    2,   58,    2, 0x0a /* Public */,
       5,    1,   63,    2, 0x2a /* Public | MethodCloned */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    1,   67,    2, 0x08 /* Private */,
      10,    1,   70,    2, 0x08 /* Private */,
      11,    1,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QFont,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    6,    7,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void GraphModelTag::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphModelTag *_t = static_cast<GraphModelTag *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tagChanged(); break;
        case 1: _t->setFont((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 2: _t->setText((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->finishEditing(); break;
        case 5: _t->textChanging((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->adjustEditBoxPosition((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setTag((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GraphModelTag::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphModelTag::tagChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject GraphModelTag::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GraphModelTag.data,
      qt_meta_data_GraphModelTag,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GraphModelTag::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphModelTag::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GraphModelTag.stringdata0))
        return static_cast<void*>(const_cast< GraphModelTag*>(this));
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(const_cast< GraphModelTag*>(this));
    return QObject::qt_metacast(_clname);
}

int GraphModelTag::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GraphModelTag::tagChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
