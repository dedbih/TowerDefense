#include <QRandomGenerator>
#include <QDebug>

class RandomEnemyGenerator
{
public:
    // Tipos de enemigos disponibles
    enum TipoEnemigo {
        ARP = 2,    // ARP.png
        ELF = 5,    // ELF.png
        OGRO = 7,   // OGRO.png
        MER = 9     // MER.png
    };

    // Obtener un tipo de enemigo aleatorio
    static int obtenerTipoAleatorio() {
        // Array con los tipos disponibles
        static const int tipos[] = {ARP, ELF, OGRO, MER};
        static const int numTipos = sizeof(tipos) / sizeof(tipos[0]);

        // Generar índice aleatorio
        int indice = QRandomGenerator::global()->bounded(numTipos);

        qDebug() << "Tipo de enemigo generado:" << tipos[indice];
        return tipos[indice];
    }

    // Obtener nombre del enemigo por tipo
    static QString obtenerNombreEnemigo(int tipo) {
        switch(tipo) {
        case ARP: return "Arpia";
        case ELF: return "Elfo";
        case OGRO: return "Ogro";
        case MER: return "Mercenario";
        default: return "Desconocido";
        }
    }

    // Obtener ruta de imagen por tipo
    static QString obtenerRutaImagen(int tipo) {
        switch(tipo) {
        case ARP: return "asset/images/ARP.png";
        case ELF: return "asset/images/ELF.png";
        case OGRO: return "asset/images/OGRO.png";
        case MER: return "asset/images/MER.png";
        default: return "";
        }
    }

    // Generar una lista de tipos aleatorios para una oleada
    static QList<int> generarOleada(int cantidad) {
        QList<int> oleada;
        for(int i = 0; i < cantidad; i++) {
            oleada.append(obtenerTipoAleatorio());
        }
        return oleada;
    }
};
