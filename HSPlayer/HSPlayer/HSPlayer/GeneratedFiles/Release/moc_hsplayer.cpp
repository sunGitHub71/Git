/****************************************************************************
** Meta object code from reading C++ file 'hsplayer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../hsplayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hsplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HSPlayer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   10,    9,    9, 0x05,
      43,   37,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,    9,    9,    9, 0x08,
      71,    9,    9,    9, 0x08,
      99,   87,    9,    9, 0x08,
     114,    9,    9,    9, 0x08,
     122,    9,    9,    9, 0x08,
     148,  140,    9,    9, 0x08,
     170,    9,    9,    9, 0x08,
     177,    9,    9,    9, 0x08,
     188,    9,    9,    9, 0x08,
     201,    9,    9,    9, 0x08,
     213,    9,    9,    9, 0x08,
     228,    9,    9,    9, 0x08,
     243,    9,    9,    9, 0x08,
     273,  254,    9,    9, 0x08,
     296,    9,    9,    9, 0x08,
     307,    9,    9,    9, 0x08,
     342,    9,    9,    9, 0x08,
     356,    9,    9,    9, 0x08,
     370,    9,    9,    9, 0x08,
     388,  384,    9,    9, 0x08,
     425,  408,    9,    9, 0x08,
     449,    9,    9,    9, 0x08,
     482,  467,    9,    9, 0x08,
     502,    9,    9,    9, 0x08,
     515,    9,    9,    9, 0x08,
     527,    9,    9,    9, 0x08,
     543,    9,    9,    9, 0x08,
     570,  559,    9,    9, 0x08,
     598,  590,    9,    9, 0x08,
     631,  626,    9,    9, 0x08,
     654,  645,    9,    9, 0x08,
     675,    9,    9,    9, 0x08,
     710,  696,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HSPlayer[] = {
    "HSPlayer\0\0isChange\0stickChange(bool)\0"
    "index\0playMode(int)\0playControl()\0"
    "videoCheckCtr()\0isOpenSound\0muteCtrl(bool)\0"
    "popup()\0getCurrentIndex()\0theList\0"
    "openFile(QStringList)\0stop()\0snapShot()\0"
    "fullScreen()\0stepByOne()\0setFastSpeed()\0"
    "setSlowSpeed()\0rightBtn()\0isContinousCapture\0"
    "continousCapture(bool)\0basicSet()\0"
    "doubleClickedAutoPlay(QModelIndex)\0"
    "DigitalZoom()\0stopCurPlay()\0stopAllPlay()\0"
    "pos\0fullScreenCtrl(int)\0isCtrlBtnEnabled\0"
    "setCtrlBtnEnabled(bool)\0captureOverNext()\0"
    "isAnyVideoPlay\0setStickOnTop(bool)\0"
    "singleMode()\0orderMode()\0repeatOneMode()\0"
    "repeatAllMode()\0videoIndex\0"
    "setCurPlayMode(int)\0theItem\0"
    "changePlayMode(LayoutItem*)\0path\0"
    "test(QString)\0fileName\0urlVideoPic(QString)\0"
    "onVideoPlayTimeOut()\0lanCode,index\0"
    "curSelectedLan(QString,int)\0"
};

void HSPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HSPlayer *_t = static_cast<HSPlayer *>(_o);
        switch (_id) {
        case 0: _t->stickChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->playMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->playControl(); break;
        case 3: _t->videoCheckCtr(); break;
        case 4: _t->muteCtrl((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->popup(); break;
        case 6: _t->getCurrentIndex(); break;
        case 7: _t->openFile((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 8: _t->stop(); break;
        case 9: _t->snapShot(); break;
        case 10: _t->fullScreen(); break;
        case 11: _t->stepByOne(); break;
        case 12: _t->setFastSpeed(); break;
        case 13: _t->setSlowSpeed(); break;
        case 14: _t->rightBtn(); break;
        case 15: _t->continousCapture((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->basicSet(); break;
        case 17: _t->doubleClickedAutoPlay((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 18: _t->DigitalZoom(); break;
        case 19: _t->stopCurPlay(); break;
        case 20: _t->stopAllPlay(); break;
        case 21: _t->fullScreenCtrl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->setCtrlBtnEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->captureOverNext(); break;
        case 24: _t->setStickOnTop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->singleMode(); break;
        case 26: _t->orderMode(); break;
        case 27: _t->repeatOneMode(); break;
        case 28: _t->repeatAllMode(); break;
        case 29: _t->setCurPlayMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->changePlayMode((*reinterpret_cast< LayoutItem*(*)>(_a[1]))); break;
        case 31: _t->test((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 32: _t->urlVideoPic((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->onVideoPlayTimeOut(); break;
        case 34: _t->curSelectedLan((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData HSPlayer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HSPlayer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HSPlayer,
      qt_meta_data_HSPlayer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HSPlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HSPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HSPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HSPlayer))
        return static_cast<void*>(const_cast< HSPlayer*>(this));
    return QWidget::qt_metacast(_clname);
}

int HSPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    return _id;
}

// SIGNAL 0
void HSPlayer::stickChange(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HSPlayer::playMode(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
