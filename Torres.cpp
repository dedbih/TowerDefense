#include <string>
#include "Enemigos.cpp"

class Torre {
protected:
    int coste;
    int alcance;
    int danno;
    int tiempo_recarga;

public:
    Torre(int c = 0, int a = 0, int d = 0, int tr = 0) :
        coste(c), alcance(a), danno(d), tiempo_recarga(tr) {}

    virtual void hacer_danno(Enemigo& enemigo, const std::string& tipo_ataque) {
        float modificador = 1.0f;

        if (tipo_ataque == "flechas") modificador = enemigo.getResistenciaFlechas();
        else if (tipo_ataque == "magia") modificador = enemigo.getResistenciaMagia();
        else if (tipo_ataque == "artilleria") modificador = enemigo.getResistenciaArtilleria();

        int dano_real = static_cast<int>(danno * modificador);
        enemigo.recibir_danno(dano_real);

    }

    void colocar_torre() {
    }
    virtual ~Torre() = default;
};


class Arquero : public Torre {
public:
    Arquero() : Torre(50, 5, 3, 1) {}
    void hacer_danno(Enemigo& enemigo, const std::string& tipo_ataque) override {
        Torre::hacer_danno(enemigo, "flechas");
    }

};

class Mago : public Torre {
public:
    Mago() : Torre(100, 4, 5, 2) {}

    void hacer_danno(Enemigo& enemigo, const std::string& tipo_ataque) override {
        Torre::hacer_danno(enemigo, "magia");
    }
};

class Artillero : public Torre {
public:
    Artillero() : Torre(150, 2, 10, 3) {}

    void hacer_danno(Enemigo& enemigo, const std::string& tipo_ataque) override {
        Torre::hacer_danno(enemigo, "artilleria");
    }
};
