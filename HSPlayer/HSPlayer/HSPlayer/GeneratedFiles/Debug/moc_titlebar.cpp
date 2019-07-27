/****************************************************************************
** Meta object code from reading C++ file 'titlebar.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../titlebar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'titlebar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TitleBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,    9,   10,    9, 0x05,
      30,   25,    9,    9, 0x05,
      57,   47,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,    9,    9,    9, 0x08,
      93,    9,    9,    9, 0x08,
     107,    9,    9,    9, 0x08,
     121,    9,    9,    9, 0x08,
     133,    9,    9,    9, 0x08,
     147,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TitleBar[] = {
    "TitleBar\0\0bool\0clicked()\0path\0"
    "UrlPath(QString)\0lan,index\0"
    "curlanCode(QString,int)\0onClicked()\0"
    "menuAddFile()\0menuOpenDir()\0menuAbout()\0"
    "menuOpenUrl()\0onCurLan()\0"
};

void TitleBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TitleBar *_t = static_cast<TitleBar *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->clicked();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: _t->UrlPath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->curlanCode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->onClicked(); break;
        case 4: _t->menuAddFile(); break;
        case 5: _t->menuOpenDir(); break;
        case 6: _t->menuAbout(); break;
        case 7: _t->menuOpenUrl(); break;
        case 8: _t->onCurLan(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TitleBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TitleBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TitleBar,
      qt_meta_data_TitleBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TitleBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TitleBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TitleBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TitleBar))
        return static_cast<void*>(const_cast< TitleBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int TitleBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
bool TitleBar::clicked()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
void TitleBar::UrlPath(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TitleBar::curlanCode(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
