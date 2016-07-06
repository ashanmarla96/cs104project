/****************************************************************************
** Meta object code from reading C++ file 'twitwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lib/twitwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'twitwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TwitWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      24,   11,   11,   11, 0x08,
      38,   11,   11,   11, 0x08,
      51,   11,   11,   11, 0x08,
      58,   11,   11,   11, 0x08,
      84,   11,   11,   11, 0x08,
     105,   11,   11,   11, 0x08,
     125,   11,   11,   11, 0x08,
     134,   11,   11,   11, 0x08,
     145,   11,   11,   11, 0x08,
     158,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TwitWindow[] = {
    "TwitWindow\0\0SaveFeeds()\0doneClicked()\0"
    "popClicked()\0quit()\0refreshfollowing(QString)\0"
    "refreshmain(QString)\0refreshmen(QString)\0"
    "search()\0tweetadd()\0followuser()\0"
    "SaveTarjan()\0"
};

void TwitWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TwitWindow *_t = static_cast<TwitWindow *>(_o);
        switch (_id) {
        case 0: _t->SaveFeeds(); break;
        case 1: _t->doneClicked(); break;
        case 2: _t->popClicked(); break;
        case 3: _t->quit(); break;
        case 4: _t->refreshfollowing((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->refreshmain((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->refreshmen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->search(); break;
        case 8: _t->tweetadd(); break;
        case 9: _t->followuser(); break;
        case 10: _t->SaveTarjan(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TwitWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TwitWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TwitWindow,
      qt_meta_data_TwitWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TwitWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TwitWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TwitWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TwitWindow))
        return static_cast<void*>(const_cast< TwitWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int TwitWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
