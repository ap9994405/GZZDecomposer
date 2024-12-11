/****************************************************************************
** Meta object code from reading C++ file 'widthmodeexportdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widthmodeexportdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widthmodeexportdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WidthModeExportDialog_t {
    QByteArrayData data[15];
    char stringdata0[302];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WidthModeExportDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WidthModeExportDialog_t qt_meta_stringdata_WidthModeExportDialog = {
    {
QT_MOC_LITERAL(0, 0, 21), // "WidthModeExportDialog"
QT_MOC_LITERAL(1, 22, 24), // "on_button_cancel_clicked"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 13), // "updatePreview"
QT_MOC_LITERAL(4, 62, 4), // "save"
QT_MOC_LITERAL(5, 67, 15), // "prepareGraphics"
QT_MOC_LITERAL(6, 83, 20), // "on_button_OK_clicked"
QT_MOC_LITERAL(7, 104, 34), // "on_horizontalSlider_2_valueCh..."
QT_MOC_LITERAL(8, 139, 5), // "value"
QT_MOC_LITERAL(9, 145, 34), // "on_horizontalSlider_3_valueCh..."
QT_MOC_LITERAL(10, 180, 34), // "on_horizontalSlider_4_valueCh..."
QT_MOC_LITERAL(11, 215, 29), // "on_checkBox_gridlines_toggled"
QT_MOC_LITERAL(12, 245, 7), // "checked"
QT_MOC_LITERAL(13, 253, 19), // "on_checkBox_toggled"
QT_MOC_LITERAL(14, 273, 28) // "on_slider_ncols_valueChanged"

    },
    "WidthModeExportDialog\0on_button_cancel_clicked\0"
    "\0updatePreview\0save\0prepareGraphics\0"
    "on_button_OK_clicked\0"
    "on_horizontalSlider_2_valueChanged\0"
    "value\0on_horizontalSlider_3_valueChanged\0"
    "on_horizontalSlider_4_valueChanged\0"
    "on_checkBox_gridlines_toggled\0checked\0"
    "on_checkBox_toggled\0on_slider_ncols_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WidthModeExportDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    1,   74,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      10,    1,   80,    2, 0x08 /* Private */,
      11,    1,   83,    2, 0x08 /* Private */,
      13,    1,   86,    2, 0x08 /* Private */,
      14,    1,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void WidthModeExportDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WidthModeExportDialog *_t = static_cast<WidthModeExportDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_button_cancel_clicked(); break;
        case 1: _t->updatePreview(); break;
        case 2: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->prepareGraphics(); break;
        case 4: _t->on_button_OK_clicked(); break;
        case 5: _t->on_horizontalSlider_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_horizontalSlider_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_horizontalSlider_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_checkBox_gridlines_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_checkBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_slider_ncols_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject WidthModeExportDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WidthModeExportDialog.data,
      qt_meta_data_WidthModeExportDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WidthModeExportDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WidthModeExportDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WidthModeExportDialog.stringdata0))
        return static_cast<void*>(const_cast< WidthModeExportDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int WidthModeExportDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
