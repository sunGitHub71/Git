/****************************************************************************
** Meta object code from reading C++ file 'playctrl.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../playctrl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playctrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayCtrl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   10,    9,    9, 0x05,
      38,    9,    9,    9, 0x05,
      50,    9,    9,    9, 0x05,
      69,    9,    9,    9, 0x05,
      80,    9,    9,    9, 0x05,
      94,    9,    9,    9, 0x05,
     108,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     123,    9,    9,    9, 0x09,
     140,    9,    9,    9, 0x09,
     161,    9,    9,    9, 0x09,
     180,    9,    9,    9, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_PlayCtrl[] = {
    "PlayCtrl\0\0isOpenSound\0soundCtrl(bool)\0"
    "startPlay()\0checkVideoSignal()\0"
    "stopPlay()\0slowForward()\0fastForward()\0"
    "frameForward()\0onTimerTimeout()\0"
    "hideOrShowPlayList()\0openOrCloseSound()\0"
    "openDir()\0"
};

void PlayCtrl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlayCtrl *_t = static_cast<PlayCtrl *>(_o);
        switch (_id) {
        case 0: _t->soundCtrl((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->startPlay(); break;
        case 2: _t->checkVideoSignal(); break;
        case 3: _t->stopPlay(); break;
        case 4: _t->slowForward(); break;
        case 5: _t->fastForward(); break;
        case 6: _t->frameForward(); break;
        case 7: _t->onTimerTimeout(); break;
        case 8: _t->hideOrShowPlayList(); break;
        case 9: _t->openOrCloseSound(); break;
        case 10: _t->openDir(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlayCtrl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlayCtrl::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayCtrl,
      qt_meta_data_PlayCtrl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayCtrl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayCtrl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayCtrl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayCtrl))
        return static_cast<void*>(const_cast< PlayCtrl*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayCtrl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void PlayCtrl::soundCtrl(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayCtrl::startPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PlayCtrl::checkVideoSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PlayCtrl::stopPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void PlayCtrl::slowForward()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void PlayCtrl::fastForward()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void PlayCtrl::frameForward()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
