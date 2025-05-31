/****************************************************************************
** Meta object code from reading C++ file 'colisiones.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../colisiones.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'colisiones.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10ColisionesE_t {};
} // unnamed namespace

template <> constexpr inline auto Colisiones::qt_create_metaobjectdata<qt_meta_tag_ZN10ColisionesE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Colisiones",
        "enemigoEliminado",
        "",
        "enemigoId",
        "tipoEnemigo",
        "dannoAplicado",
        "dannoRealizado",
        "verificarImpactoProyectil",
        "posicionProyectil",
        "QList<Enemigo>",
        "enemigos",
        "encontrarEnemigoEnPosicion",
        "posicion",
        "aplicarDanno",
        "danno",
        "tipoAtaque",
        "QList<Enemigo>&",
        "calcularDistancia",
        "p1",
        "p2",
        "estaEnRango",
        "posicionTorre",
        "posicionEnemigo",
        "alcance"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'enemigoEliminado'
        QtMocHelpers::SignalData<void(int, int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::Int, 4 },
        }}),
        // Signal 'dannoAplicado'
        QtMocHelpers::SignalData<void(int, int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::Int, 6 },
        }}),
        // Method 'verificarImpactoProyectil'
        QtMocHelpers::MethodData<bool(QPoint, const QList<Enemigo> &)>(7, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QPoint, 8 }, { 0x80000000 | 9, 10 },
        }}),
        // Method 'encontrarEnemigoEnPosicion'
        QtMocHelpers::MethodData<int(QPoint, const QList<Enemigo> &)>(11, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::QPoint, 12 }, { 0x80000000 | 9, 10 },
        }}),
        // Method 'aplicarDanno'
        QtMocHelpers::MethodData<bool(int, int, QString, QList<Enemigo> &)>(13, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 3 }, { QMetaType::Int, 14 }, { QMetaType::QString, 15 }, { 0x80000000 | 16, 10 },
        }}),
        // Method 'calcularDistancia'
        QtMocHelpers::MethodData<float(QPoint, QPoint)>(17, 2, QMC::AccessPublic, QMetaType::Float, {{
            { QMetaType::QPoint, 18 }, { QMetaType::QPoint, 19 },
        }}),
        // Method 'estaEnRango'
        QtMocHelpers::MethodData<bool(QPoint, QPoint, int)>(20, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QPoint, 21 }, { QMetaType::QPoint, 22 }, { QMetaType::Int, 23 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Colisiones, qt_meta_tag_ZN10ColisionesE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Colisiones::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ColisionesE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ColisionesE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10ColisionesE_t>.metaTypes,
    nullptr
} };

void Colisiones::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Colisiones *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->enemigoEliminado((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->dannoAplicado((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: { bool _r = _t->verificarImpactoProyectil((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<Enemigo>>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->encontrarEnemigoEnPosicion((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<Enemigo>>>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->aplicarDanno((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QList<Enemigo>&>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { float _r = _t->calcularDistancia((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->estaEnRango((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Colisiones::*)(int , int )>(_a, &Colisiones::enemigoEliminado, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Colisiones::*)(int , int )>(_a, &Colisiones::dannoAplicado, 1))
            return;
    }
}

const QMetaObject *Colisiones::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Colisiones::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ColisionesE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Colisiones::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Colisiones::enemigoEliminado(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void Colisiones::dannoAplicado(int _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}
QT_WARNING_POP
