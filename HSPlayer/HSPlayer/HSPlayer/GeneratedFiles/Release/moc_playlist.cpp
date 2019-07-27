/****************************************************************************
** Meta object code from reading C++ file 'playlist.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../playlist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayList[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      26,    9,    9,    9, 0x05,
      42,    9,    9,    9, 0x05,
      54,    9,    9,    9, 0x05,
      81,    9,    9,    9, 0x05,
      93,    9,    9,    9, 0x05,
     106,    9,    9,    9, 0x05,
     118,    9,    9,    9, 0x05,
     134,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     150,    9,    9,    9, 0x08,
     163,    9,    9,    9, 0x08,
     180,  174,    9,    9, 0x08,
     207,    9,    9,    9, 0x08,
     223,    9,    9,    9, 0x08,
     242,    9,    9,    9, 0x08,
     252,    9,    9,    9, 0x08,
     266,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PlayList[] = {
    "PlayList\0\0deleteCurOver()\0deleteAllOver()\0"
    "rightPlay()\0doubleClicked(QModelIndex)\0"
    "endSearch()\0singlePlay()\0orderPlay()\0"
    "repeatOnePlay()\0repeatAllPlay()\0"
    "Opensearch()\0setClick()\0index\0"
    "getModelIndex(QModelIndex)\0deleteCurFile()\0"
    "clearCurFileList()\0addFile()\0startSearch()\0"
    "restorePlayList()\0"
};

void PlayList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlayList *_t = static_cast<PlayList *>(_o);
        switch (_id) {
        case 0: _t->deleteCurOver(); break;
        case 1: _t->deleteAllOver(); break;
        case 2: _t->rightPlay(); break;
        case 3: _t->doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->endSearch(); break;
        case 5: _t->singlePlay(); break;
        case 6: _t->orderPlay(); break;
        case 7: _t->repeatOnePlay(); break;
        case 8: _t->repeatAllPlay(); break;
        case 9: _t->Opensearch(); break;
        case 10: _t->setClick(); break;
        case 11: _t->getModelIndex((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 12: _t->deleteCurFile(); break;
        case 13: _t->clearCurFileList(); break;
        case 14: _t->addFile(); break;
        case 15: _t->startSearch(); break;
        case 16: _t->restorePlayList(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlayList::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlayList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayList,
      qt_meta_data_PlayList, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayList))
        return static_cast<void*>(const_cast< PlayList*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void PlayList::deleteCurOver()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PlayList::deleteAllOver()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PlayList::rightPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PlayList::doubleClicked(const QModelIndex & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayList::endSearch()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void PlayList::singlePlay()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void PlayList::orderPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void PlayList::repeatOnePlay()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void PlayList::repeatAllPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
