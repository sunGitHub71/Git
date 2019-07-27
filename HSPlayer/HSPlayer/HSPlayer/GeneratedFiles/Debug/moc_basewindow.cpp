/****************************************************************************
** Meta object code from reading C++ file 'basewindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../basewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BaseWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      33,   11,   11,   11, 0x08,
      58,   11,   11,   11, 0x08,
      79,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BaseWindow[] = {
    "BaseWindow\0\0onButtonMinClicked()\0"
    "onButtonRestoreClicked()\0onButtonMaxClicked()\0"
    "onButtonCloseClicked()\0"
};

void BaseWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BaseWindow *_t = static_cast<BaseWindow *>(_o);
        switch (_id) {
        case 0: _t->onButtonMinClicked(); break;
        case 1: _t->onButtonRestoreClicked(); break;
        case 2: _t->onButtonMaxClicked(); break;
        case 3: _t->onButtonCloseClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BaseWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BaseWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BaseWindow,
      qt_meta_data_BaseWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BaseWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BaseWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BaseWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BaseWindow))
        return static_cast<void*>(const_cast< BaseWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int BaseWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
