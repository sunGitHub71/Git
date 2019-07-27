/****************************************************************************
** Meta object code from reading C++ file 'CheckVideoWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CheckVideoWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CheckVideoWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CheckVideo_TableModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   23,   22,   22, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CheckVideo_TableModel[] = {
    "CheckVideo_TableModel\0\0count\0"
    "updateCount(int)\0"
};

void CheckVideo_TableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckVideo_TableModel *_t = static_cast<CheckVideo_TableModel *>(_o);
        switch (_id) {
        case 0: _t->updateCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CheckVideo_TableModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckVideo_TableModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_CheckVideo_TableModel,
      qt_meta_data_CheckVideo_TableModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckVideo_TableModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckVideo_TableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckVideo_TableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckVideo_TableModel))
        return static_cast<void*>(const_cast< CheckVideo_TableModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int CheckVideo_TableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CheckVideo_TableModel::updateCount(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_CheckVideo_TableView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_CheckVideo_TableView[] = {
    "CheckVideo_TableView\0"
};

void CheckVideo_TableView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CheckVideo_TableView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckVideo_TableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_CheckVideo_TableView,
      qt_meta_data_CheckVideo_TableView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckVideo_TableView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckVideo_TableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckVideo_TableView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckVideo_TableView))
        return static_cast<void*>(const_cast< CheckVideo_TableView*>(this));
    return QTableView::qt_metacast(_clname);
}

int CheckVideo_TableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_CheckVideoWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      47,   38,   17,   17, 0x08,
      72,   38,   17,   17, 0x08,
     103,   17,   17,   17, 0x08,
     122,   17,   17,   17, 0x08,
     141,  136,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CheckVideoWidget[] = {
    "CheckVideoWidget\0\0onStartBtnClicked()\0"
    "fileInfo\0onCheckFile(QStringList)\0"
    "onCheckFileUpdate(QStringList)\0"
    "onStopBtnClicked()\0onCheckOver()\0item\0"
    "onShowListTooltip(QListWidgetItem*)\0"
};

void CheckVideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckVideoWidget *_t = static_cast<CheckVideoWidget *>(_o);
        switch (_id) {
        case 0: _t->onStartBtnClicked(); break;
        case 1: _t->onCheckFile((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->onCheckFileUpdate((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->onStopBtnClicked(); break;
        case 4: _t->onCheckOver(); break;
        case 5: _t->onShowListTooltip((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CheckVideoWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckVideoWidget::staticMetaObject = {
    { &BaseWindow::staticMetaObject, qt_meta_stringdata_CheckVideoWidget,
      qt_meta_data_CheckVideoWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckVideoWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckVideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckVideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckVideoWidget))
        return static_cast<void*>(const_cast< CheckVideoWidget*>(this));
    return BaseWindow::qt_metacast(_clname);
}

int CheckVideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
