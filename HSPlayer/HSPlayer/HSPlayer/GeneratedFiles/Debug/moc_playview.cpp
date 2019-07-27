/****************************************************************************
** Meta object code from reading C++ file 'playview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../playview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   10,    9,    9, 0x05,
      42,    9,    9,    9, 0x05,
      68,   56,    9,    9, 0x05,
     106,   97,    9,    9, 0x05,
     149,  144,    9,    9, 0x05,
     173,  163,    9,    9, 0x05,
     194,    9,    9,    9, 0x05,
     218,  208,    9,    9, 0x05,
     247,  239,    9,    9, 0x05,
     269,   10,    9,    9, 0x05,
     293,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     320,  312,    9,    9, 0x08,
     363,  353,    9,    9, 0x08,
     394,  389,    9,    9, 0x08,
     425,  416,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PlayView[] = {
    "PlayView\0\0fileName\0dropItemPlay(QString*)\0"
    "curOverPlay()\0curOpenList\0"
    "curOpenFileList(QStringList)\0item,pos\0"
    "toolBarCurStatus(VideoWidget*,QPoint)\0"
    "cury\0toolBarY(int)\0isEnabled\0"
    "ctrlBtnEnabled(bool)\0captureOver()\0"
    "videoPlay\0isAnyVideoPlay(bool)\0curItem\0"
    "overPlay(LayoutItem*)\0urlPlaySuccess(QString)\0"
    "videoPlayTimeOut()\0theItem\0"
    "onItemNewNodeDroped(LayoutItem*)\0"
    "item,posy\0posy(VideoWidget*,QPoint)\0"
    "item\0playThen(LayoutItem*)\0thisItem\0"
    "stopThen(LayoutItem*)\0"
};

void PlayView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlayView *_t = static_cast<PlayView *>(_o);
        switch (_id) {
        case 0: _t->dropItemPlay((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        case 1: _t->curOverPlay(); break;
        case 2: _t->curOpenFileList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->toolBarCurStatus((*reinterpret_cast< VideoWidget*(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 4: _t->toolBarY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->ctrlBtnEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->captureOver(); break;
        case 7: _t->isAnyVideoPlay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->overPlay((*reinterpret_cast< LayoutItem*(*)>(_a[1]))); break;
        case 9: _t->urlPlaySuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->videoPlayTimeOut(); break;
        case 11: _t->onItemNewNodeDroped((*reinterpret_cast< LayoutItem*(*)>(_a[1]))); break;
        case 12: _t->posy((*reinterpret_cast< VideoWidget*(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 13: _t->playThen((*reinterpret_cast< LayoutItem*(*)>(_a[1]))); break;
        case 14: _t->stopThen((*reinterpret_cast< LayoutItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlayView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlayView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayView,
      qt_meta_data_PlayView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayView))
        return static_cast<void*>(const_cast< PlayView*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void PlayView::dropItemPlay(QString * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayView::curOverPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PlayView::curOpenFileList(QStringList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayView::toolBarCurStatus(VideoWidget * _t1, QPoint _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayView::toolBarY(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PlayView::ctrlBtnEnabled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PlayView::captureOver()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void PlayView::isAnyVideoPlay(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PlayView::overPlay(LayoutItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void PlayView::urlPlaySuccess(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PlayView::videoPlayTimeOut()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}
QT_END_MOC_NAMESPACE
