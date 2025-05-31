/****************************************************************************
** Meta object code from reading C++ file 'oleadas.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../oleadas.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oleadas.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN7OleadasE_t {};
} // unnamed namespace

template <> constexpr inline auto Oleadas::qt_create_metaobjectdata<qt_meta_tag_ZN7OleadasE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Oleadas",
        "oleadaActivaChanged",
        "",
        "enemigosRestantesChanged",
        "enemigosEnCampoChanged",
        "enemigoLlegoDestino",
        "tipoEnemigo",
        "oleadaCompletada",
        "gridActualizado",
        "procesarOleada",
        "iniciarOleada",
        "QList<QPoint>",
        "ruta",
        "QVariantList&",
        "gridData",
        "detenerOleada",
        "pausarOleada",
        "reanudarOleada",
        "oleadaActiva",
        "enemigosRestantes",
        "enemigosEnCampo"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'oleadaActivaChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'enemigosRestantesChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'enemigosEnCampoChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'enemigoLlegoDestino'
        QtMocHelpers::SignalData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Signal 'oleadaCompletada'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gridActualizado'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'procesarOleada'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Method 'iniciarOleada'
        QtMocHelpers::MethodData<void(const QList<QPoint> &, QVariantList &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 }, { 0x80000000 | 13, 14 },
        }}),
        // Method 'detenerOleada'
        QtMocHelpers::MethodData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'pausarOleada'
        QtMocHelpers::MethodData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'reanudarOleada'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'oleadaActiva'
        QtMocHelpers::PropertyData<bool>(18, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'enemigosRestantes'
        QtMocHelpers::PropertyData<int>(19, QMetaType::Int, QMC::DefaultPropertyFlags, 1),
        // property 'enemigosEnCampo'
        QtMocHelpers::PropertyData<int>(20, QMetaType::Int, QMC::DefaultPropertyFlags, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Oleadas, qt_meta_tag_ZN7OleadasE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Oleadas::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7OleadasE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7OleadasE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN7OleadasE_t>.metaTypes,
    nullptr
} };

void Oleadas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Oleadas *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->oleadaActivaChanged(); break;
        case 1: _t->enemigosRestantesChanged(); break;
        case 2: _t->enemigosEnCampoChanged(); break;
        case 3: _t->enemigoLlegoDestino((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->oleadaCompletada(); break;
        case 5: _t->gridActualizado(); break;
        case 6: _t->procesarOleada(); break;
        case 7: _t->iniciarOleada((*reinterpret_cast< std::add_pointer_t<QList<QPoint>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantList&>>(_a[2]))); break;
        case 8: _t->detenerOleada(); break;
        case 9: _t->pausarOleada(); break;
        case 10: _t->reanudarOleada(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QPoint> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Oleadas::*)()>(_a, &Oleadas::oleadaActivaChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Oleadas::*)()>(_a, &Oleadas::enemigosRestantesChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Oleadas::*)()>(_a, &Oleadas::enemigosEnCampoChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Oleadas::*)(int )>(_a, &Oleadas::enemigoLlegoDestino, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Oleadas::*)()>(_a, &Oleadas::oleadaCompletada, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Oleadas::*)()>(_a, &Oleadas::gridActualizado, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->oleadaActiva(); break;
        case 1: *reinterpret_cast<int*>(_v) = _t->enemigosRestantes(); break;
        case 2: *reinterpret_cast<int*>(_v) = _t->enemigosEnCampo(); break;
        default: break;
        }
    }
}

const QMetaObject *Oleadas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Oleadas::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN7OleadasE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Oleadas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Oleadas::oleadaActivaChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Oleadas::enemigosRestantesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Oleadas::enemigosEnCampoChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Oleadas::enemigoLlegoDestino(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Oleadas::oleadaCompletada()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Oleadas::gridActualizado()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
