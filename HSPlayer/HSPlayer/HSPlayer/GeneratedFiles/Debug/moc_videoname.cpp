/****************************************************************************
** Meta object code from reading C++ file 'videoname.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../videoname.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoname.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VideoName[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   11,   10,   10, 0x05,
      53,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VideoName[] = {
    "VideoName\0\0isContinousCapture\0"
    "continousCapture(bool)\0fullScreen()\0"
    "getIscontinuousCapture()\0"
};

void VideoName::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VideoName *_t = static_cast<VideoName *>(_o);
        switch (_id) {
        case 0: _t->continousCapture((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->fullScreen(); break;
        case 2: _t->getIscontinuousCapture(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VideoName::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VideoName::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoName,
      qt_meta_data_VideoName, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VideoName::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VideoName::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VideoName::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VideoName))
        return static_cast<void*>(const_cast< VideoName*>(this));
    return QWidget::qt_metacast(_clname);
}

int VideoName::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void VideoName::continousCapture(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VideoName::fullScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
