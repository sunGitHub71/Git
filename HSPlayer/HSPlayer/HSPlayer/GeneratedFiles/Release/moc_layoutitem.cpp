/****************************************************************************
** Meta object code from reading C++ file 'layoutitem.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../layoutitem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'layoutitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LayoutItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x05,
      59,   47,   11,   11, 0x05,
      89,   80,   11,   11, 0x05,
     124,   11,   11,   11, 0x05,
     151,  143,   11,   11, 0x05,
     178,  173,   11,   11, 0x05,
     214,  205,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     239,   11,   11,   11, 0x08,
     254,   11,   11,   11, 0x08,
     276,   11,   11,   11, 0x08,
     293,   11,   11,   11, 0x08,
     312,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LayoutItem[] = {
    "LayoutItem\0\0theItem\0newNodeDroped(LayoutItem*)\0"
    "curOpenList\0curList(QStringList)\0"
    "item,pos\0toolBarStatus(VideoWidget*,QPoint)\0"
    "captureCompleted()\0curItem\0"
    "overplay(LayoutItem*)\0item\0"
    "startPlayItem(LayoutItem*)\0thisItem\0"
    "endPlayItem(LayoutItem*)\0startCapture()\0"
    "onPlayTimerTimerout()\0curItemrefresh()\0"
    "startDigitalZoom()\0hideInfo()\0"
};

void LayoutItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LayoutItem *_t = static_cast<LayoutItem *>(_o);
        switch (_id) {
        case 0: _t->newNodeDroped((*reinterpret_cast< LayoutItem*(*)>(_a[1]))); break;
        case 1: _t->curList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->toolBarStatus((*reinterpret_cast< VideoWidget*(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 3: _t->captureCompleted(); break;
        case 4: _t->overplay((*reinterpret_cast< LayoutItem*(*)>(_a[1]))); break;
        case 5: _t->startPlayItem((*reinterpret_cast< LayoutItem*(*)>(_a[1]))); break;
        case 6: _t->endPlayItem((*reinterpret_cast< LayoutItem*(*)>(_a[1]))); break;
        case 7: _t->startCapture(); break;
        case 8: _t->onPlayTimerTimerout(); break;
        case 9: _t->curItemrefresh(); break;
        case 10: _t->startDigitalZoom(); break;
        case 11: _t->hideInfo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LayoutItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LayoutItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LayoutItem,
      qt_meta_data_LayoutItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LayoutItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LayoutItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LayoutItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LayoutItem))
        return static_cast<void*>(const_cast< LayoutItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int LayoutItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void LayoutItem::newNodeDroped(LayoutItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LayoutItem::curList(QStringList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LayoutItem::toolBarStatus(VideoWidget * _t1, QPoint _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LayoutItem::captureCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void LayoutItem::overplay(LayoutItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LayoutItem::startPlayItem(LayoutItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void LayoutItem::endPlayItem(LayoutItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
