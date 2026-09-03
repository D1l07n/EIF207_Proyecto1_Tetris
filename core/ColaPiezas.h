#pragma once
#include "TipoPieza.h"

class ColaPiezas {
public:
    ColaPiezas();
    ~ColaPiezas();

    TipoPieza desencolar();
    TipoPieza verEnPosicion(int posicion) const;
    bool isEmpty() const;

private:
    struct Nodo {
        TipoPieza dato;
        Nodo* sig;
        Nodo(TipoPieza d) : dato(d), sig(nullptr) {}
    };

    Nodo* inicio;
    Nodo* final;
    int cantidadActual;   // evita tener que recorrer para saber cuantas hay

    void encolar(TipoPieza v);
    void generarYEncolarBolsa();
};