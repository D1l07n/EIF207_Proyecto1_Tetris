#pragma once
#include "TipoEvento.h"

class ColaEventos {
public:
    ColaEventos();
    ~ColaEventos();

    bool isEmpty() const;

   
    void insertar(TipoEvento tipo, float tiempoDisparo);

    
    bool hayEventoListo(float tiempoActual) const;

    TipoEvento extraerProximo();

private:
    struct NodoEvento {
        TipoEvento tipo;
        float tiempoDisparo;
        NodoEvento* sig;

        NodoEvento(TipoEvento t, float tD) : tipo(t), tiempoDisparo(tD), sig(nullptr) {}
    };

    NodoEvento* inicio;
};
