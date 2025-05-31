#include "oleadas.h"
#include <QDebug>
#include <QRandomGenerator>

// Incluir la clase RandomEnemyGenerator
class RandomEnemyGenerator
{
public:
    enum TipoEnemigo {
        ARP = 2,    // ARP.png
        ELF = 5,    // ELF.png
        OGRO = 7,   // OGRO.png
        MER = 9     // MER.png
    };

    static int obtenerTipoAleatorio() {
        static const int tipos[] = {ARP, ELF, OGRO, MER};
        static const int numTipos = sizeof(tipos) / sizeof(tipos[0]);
        int indice = QRandomGenerator::global()->bounded(numTipos);
        return tipos[indice];
    }
};

Oleadas::Oleadas(QObject *parent)
    : QObject(parent)
    , m_oleadaActiva(false)
    , m_enemigosRestantes(0)
    , m_enemigosEnCampo(0)
    , m_siguienteEnemigoPorGenerar(0)
    , m_velocidadMovimiento(600)  // 600ms entre movimientos
    , m_distanciaEntreEnemigos(2) // 2 casillas de distancia
    , m_maxEnemigos(4)            // 4 enemigos por oleada
    , m_gridData(nullptr)
{
    // Configurar timer principal
    connect(&m_timerPrincipal, &QTimer::timeout, this, &Oleadas::procesarOleada);
}

void Oleadas::iniciarOleada(const QList<QPoint> &ruta, QVariantList &gridData)
{
    if (m_oleadaActiva) {
        qDebug() << "Ya hay una oleada activa";
        return;
    }

    if (ruta.isEmpty()) {
        qDebug() << "No hay ruta disponible para la oleada";
        return;
    }

    // Configurar datos
    m_ruta = ruta;
    m_gridData = &gridData;

    // Reiniciar variables
    m_oleadaActiva = true;
    m_enemigosRestantes = m_maxEnemigos;
    m_enemigosEnCampo = 0;
    m_siguienteEnemigoPorGenerar = 0;

    // Limpiar enemigos anteriores
    m_enemigos.clear();

    // Inicializar enemigos
    inicializarEnemigos();

    // Iniciar timer principal
    m_timerPrincipal.start(m_velocidadMovimiento);

    emit oleadaActivaChanged();
    emit enemigosRestantesChanged();
    emit enemigosEnCampoChanged();

    qDebug() << "Oleada iniciada con" << m_maxEnemigos << "enemigos";
}

void Oleadas::detenerOleada()
{
    if (!m_oleadaActiva) return;

    // Detener timer
    m_timerPrincipal.stop();

    // Limpiar grid de enemigos
    limpiarGrid();

    // Reiniciar estado
    m_oleadaActiva = false;
    m_enemigosRestantes = 0;
    m_enemigosEnCampo = 0;
    m_siguienteEnemigoPorGenerar = 0;
    m_enemigos.clear();

    emit oleadaActivaChanged();
    emit enemigosRestantesChanged();
    emit enemigosEnCampoChanged();
    emit gridActualizado();

    qDebug() << "Oleada detenida";
}

void Oleadas::pausarOleada()
{
    if (!m_oleadaActiva) return;
    m_timerPrincipal.stop();
    qDebug() << "Oleada pausada";
}

void Oleadas::reanudarOleada()
{
    if (!m_oleadaActiva) return;
    m_timerPrincipal.start(m_velocidadMovimiento);
    qDebug() << "Oleada reanudada";
}

void Oleadas::procesarOleada()
{
    if (!m_oleadaActiva || !m_gridData) return;

    // Limpiar grid de enemigos
    limpiarGrid();

    // 1. Generar nuevo enemigo si es posible
    if (puedeGenerarNuevoEnemigo()) {
        generarSiguienteEnemigo();
    }

    // 2. Mover todos los enemigos activos
    moverEnemigos();

    // 3. Actualizar grid con nuevas posiciones
    actualizarGridConEnemigos();

    // 4. Verificar si la oleada ha terminado
    if (m_enemigosRestantes <= 0 && m_enemigosEnCampo <= 0) {
        detenerOleada();
        emit oleadaCompletada();
        qDebug() << "Oleada completada";
    }

    emit gridActualizado();
}

void Oleadas::inicializarEnemigos()
{
    m_enemigos.clear();

    // Crear enemigos con tipos aleatorios
    for (int i = 0; i < m_maxEnemigos; i++) {
        int tipoAleatorio = obtenerTipoEnemigoAleatorio();
        Enemigo enemigo(i, tipoAleatorio);
        m_enemigos.append(enemigo);
    }

    qDebug() << "Enemigos inicializados:" << m_enemigos.size();
}

bool Oleadas::puedeGenerarNuevoEnemigo()
{
    // Verificar si quedan enemigos por generar
    if (m_siguienteEnemigoPorGenerar >= m_maxEnemigos) {
        return false;
    }

    // Verificar si hay espacio en la posición inicial
    return hayEspacioEnInicio();
}

bool Oleadas::hayEspacioEnInicio()
{
    QPoint posInicial = obtenerPosicionInicial();

    // Verificar si algún enemigo activo está en la posición inicial
    for (const Enemigo &enemigo : m_enemigos) {
        if (enemigo.activo && enemigo.posicion == posInicial) {
            return false;
        }
    }

    return true;
}

void Oleadas::generarSiguienteEnemigo()
{
    if (m_siguienteEnemigoPorGenerar >= m_enemigos.size()) return;

    Enemigo &enemigo = m_enemigos[m_siguienteEnemigoPorGenerar];
    enemigo.activo = true;
    enemigo.enEspera = false;
    enemigo.posicion = obtenerPosicionInicial();
    enemigo.indicePath = 0;

    m_siguienteEnemigoPorGenerar++;
    m_enemigosEnCampo++;
    m_enemigosRestantes--;

    emit enemigosRestantesChanged();
    emit enemigosEnCampoChanged();

    qDebug() << "Enemigo:" << enemigo.id << "Tipo:" << enemigo.tipo;
}

void Oleadas::moverEnemigos()
{
    // Mover enemigos desde el último hacia el primero para evitar colisiones
    for (int i = m_enemigos.size() - 1; i >= 0; i--) {
        if (m_enemigos[i].activo && !m_enemigos[i].llegoDest) {
            moverEnemigo(m_enemigos[i]);
        }
    }
}

void Oleadas::moverEnemigo(Enemigo &enemigo)
{
    // Verificar si el enemigo ha llegado al final de la ruta
    if (enemigo.indicePath >= m_ruta.size()) {
        // El enemigo ha llegado al destino
        enemigo.llegoDest = true;
        enemigo.activo = false;
        eliminarEnemigoDeCampo(enemigo.id);

        emit enemigoLlegoDestino(enemigo.tipo);

        qDebug() << "El Enemigo llego al castillo";
        return;
    }

    // Obtener siguiente posición en la ruta
    QPoint siguientePosicion = m_ruta[enemigo.indicePath];

    // Verificar si hay otro enemigo en la siguiente posición
    bool hayColision = false;
    for (const Enemigo &otroEnemigo : m_enemigos) {
        if (otroEnemigo.id != enemigo.id && otroEnemigo.activo &&
            otroEnemigo.posicion == siguientePosicion) {
            hayColision = true;
            break;
        }
    }

    // Si no hay colisión, mover el enemigo
    if (!hayColision) {
        enemigo.posicion = siguientePosicion;
        enemigo.indicePath++;
    }
    // Si hay colisión, el enemigo se queda en su posición actual (espera)
}

QPoint Oleadas::obtenerPosicionInicial()
{
    // Retornar la primera posición de la ruta
    if (!m_ruta.isEmpty()) {
        return m_ruta.first();
    }
    return QPoint(-1, -1);
}

void Oleadas::eliminarEnemigoDeCampo(int id)
{
    m_enemigosEnCampo--;
    emit enemigosEnCampoChanged();
}

void Oleadas::limpiarGrid()
{
    if (!m_gridData) return;

    // Limpiar posiciones de enemigos anteriores (tipos 2, 5, 7, 9)
    for (int i = 0; i < m_gridData->size(); i++) {
        int valor = m_gridData->at(i).toInt();
        if (valor == 2 || valor == 5 || valor == 7 || valor == 9) {
            (*m_gridData)[i] = 1; // Cambiar a camino
        }
    }
}

void Oleadas::actualizarGridConEnemigos()
{
    if (!m_gridData) return;

    // Colocar enemigos activos en el grid
    for (const Enemigo &enemigo : m_enemigos) {
        if (enemigo.activo && !enemigo.llegoDest &&
            enemigo.posicion.x() >= 0 && enemigo.posicion.y() >= 0) {

            int index = getGridIndex(enemigo.posicion);
            if (index >= 0 && index < m_gridData->size()) {
                (*m_gridData)[index] = enemigo.tipo;
            }
        }
    }
}

int Oleadas::getGridIndex(const QPoint &pos)
{
    // Convertir posición (fila, columna) a índice del grid
    return pos.x() * 32 + pos.y(); // 32 columnas
}

int Oleadas::obtenerTipoEnemigoAleatorio()
{
    return RandomEnemyGenerator::obtenerTipoAleatorio();
}

