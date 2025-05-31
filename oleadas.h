#ifndef OLEADAS_H
#define OLEADAS_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <QPoint>
#include <QVariantList>

// Estructura para representar un enemigo
struct Enemigo {
    int id;
    int tipo;           // Tipo de enemigo (2, 5, 7, 9 para ARP, ELF, OGRO, MER)
    QPoint posicion;    // Posición actual en el grid
    int indicePath;     // Índice actual en la ruta
    bool activo;        // Si el enemigo está activo en el campo
    bool llegoDest;     // Si el enemigo llegó al destino
    bool enEspera;      // Si el enemigo está esperando para salir

    Enemigo() : id(0), tipo(2), posicion(-1, -1), indicePath(-1), activo(false), llegoDest(false), enEspera(true) {}
    Enemigo(int _id, int _tipo) : id(_id), tipo(_tipo), posicion(-1, -1), indicePath(-1), activo(false), llegoDest(false), enEspera(true) {}
};

class Oleadas : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool oleadaActiva READ oleadaActiva NOTIFY oleadaActivaChanged)
    Q_PROPERTY(int enemigosRestantes READ enemigosRestantes NOTIFY enemigosRestantesChanged)
    Q_PROPERTY(int enemigosEnCampo READ enemigosEnCampo NOTIFY enemigosEnCampoChanged)

public:
    explicit Oleadas(QObject *parent = nullptr);

    // Propiedades
    bool oleadaActiva() const { return m_oleadaActiva; }
    int enemigosRestantes() const { return m_enemigosRestantes; }
    int enemigosEnCampo() const { return m_enemigosEnCampo; }

    // Métodos públicos
    Q_INVOKABLE void iniciarOleada(const QList<QPoint> &ruta, QVariantList &gridData);
    Q_INVOKABLE void detenerOleada();
    Q_INVOKABLE void pausarOleada();
    Q_INVOKABLE void reanudarOleada();

    // Configuración
    void setVelocidadMovimiento(int ms) { m_velocidadMovimiento = ms; }
    void setDistanciaEntreEnemigos(int distancia) { m_distanciaEntreEnemigos = distancia; }

signals:
    void oleadaActivaChanged();
    void enemigosRestantesChanged();
    void enemigosEnCampoChanged();
    void enemigoLlegoDestino(int tipoEnemigo);
    void oleadaCompletada();
    void gridActualizado();

private slots:
    void procesarOleada();

private:
    // Variables de estado
    bool m_oleadaActiva;
    int m_enemigosRestantes;
    int m_enemigosEnCampo;
    int m_siguienteEnemigoPorGenerar;

    // Configuración
    int m_velocidadMovimiento;
    int m_distanciaEntreEnemigos;
    int m_maxEnemigos;

    // Datos de la oleada
    QList<Enemigo> m_enemigos;
    QList<QPoint> m_ruta;
    QVariantList *m_gridData;

    // Timer Main
    QTimer m_timerPrincipal;

    // Métodos privados
    void inicializarEnemigos();
    void limpiarGrid();
    void actualizarGridConEnemigos();
    void generarSiguienteEnemigo();
    void moverEnemigos();
    QPoint obtenerPosicionInicial();
    void moverEnemigo(Enemigo &enemigo);
    bool puedeGenerarNuevoEnemigo();
    bool hayEspacioEnInicio();
    void eliminarEnemigoDeCampo(int id);
    int obtenerTipoEnemigoAleatorio();
    int getGridIndex(const QPoint &pos);
};

#endif // OLEADAS_H
