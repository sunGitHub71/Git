/****************************************************************************
** Meta object code from reading C++ file 'CheckMD5Thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CheckMD5Thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CheckMD5Thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CheckMD5Thread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   16,   15,   15, 0x05,
      43,   16,   15,   15, 0x05,
      72,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      88,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CheckMD5Thread[] = {
    "CheckMD5Thread\0\0tep\0MsgSignal(QStringList)\0"
    "MsgSignalUpdate(QStringList)\0"
    "MsgSignalOver()\0stopImmediately()\0"
};

void CheckMD5Thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckMD5Thread *_t = static_cast<CheckMD5Thread *>(_o);
        switch (_id) {
        case 0: _t->MsgSignal((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->MsgSignalUpdate((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->MsgSignalOver(); break;
        case 3: _t->stopImmediately(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CheckMD5Thread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckMD5Thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CheckMD5Thread,
      qt_meta_data_CheckMD5Thread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckMD5Thread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckMD5Thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckMD5Thread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckMD5Thread))
        return static_cast<void*>(const_cast< CheckMD5Thread*>(this));
    return QThread::qt_metacast(_clname);
}

int CheckMD5Thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CheckMD5Thread::MsgSignal(QStringList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CheckMD5Thread::MsgSignalUpdate(QStringList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CheckMD5Thread::MsgSignalOver()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
