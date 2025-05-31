
class Enemigo {
protected:
    int vida=10;
    int velocidad=0;
    float resistencia_flechas=1.0f;
    float resistencia_magia=1.0f;
    float resistencia_artilleria=1.0f;
public:
    //pathFinder.moveCharacter();
    void morir();
    void hacer_danno();
    void recibir_danno(int cantidad){
        vida -=cantidad;
    }

    float getResistenciaFlechas() const { return resistencia_flechas; }
    float getResistenciaMagia() const { return resistencia_magia; }
    float getResistenciaArtilleria() const { return resistencia_artilleria; }

};

class Mercenario : public Enemigo {
public:
    Mercenario() {
        vida = 10;
        velocidad = 2;
        resistencia_flechas = 0.5f;
        resistencia_magia = 1.5f;
        resistencia_artilleria = 0.5f;
    }
};

class Arpia : public Enemigo {
public:
    Arpia() {
        vida = 12;
        velocidad = 2;
        resistencia_flechas = 0.5f;
        resistencia_magia = 0.5f;
        resistencia_artilleria = 999.0f; //resistencia alta que simule la inmunidad
    }
};

class ElfoOscuro : public Enemigo {
public:
    ElfoOscuro() {
        vida = 15;
        velocidad = 3;
        resistencia_flechas = 1.5f;
        resistencia_magia = 0.5f;
        resistencia_artilleria = 1.5f;
    }
};

class Ogro : public Enemigo {
public:
    Ogro() {
        vida = 20;
        velocidad = 1;
        resistencia_flechas = 0.5f;
        resistencia_magia = 1.5f;
        resistencia_artilleria = 1.5f;
    }
};
