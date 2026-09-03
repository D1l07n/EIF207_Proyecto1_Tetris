#include "ColaEventos.h"

ColaEventos::ColaEventos() : inicio(nullptr) {
}

ColaEventos::~ColaEventos() {
    while (!isEmpty()) {
        extraerProximo();
    }
}

bool ColaEventos::isEmpty() const {
    return inicio == nullptr;
}

void ColaEventos::insertar(TipoEvento tipo, float tiempoDisparo) {
    NodoEvento* nuevo = new NodoEvento(tipo, tiempoDisparo);

    
    if (inicio == nullptr || tiempoDisparo < inicio->tiempoDisparo) {
        nuevo->sig = inicio;
        inicio = nuevo;
        return;
    }

    
    NodoEvento* actual = inicio;
    while (actual->sig != nullptr && actual->sig->tiempoDisparo <= tiempoDisparo) {
        actual = actual->sig;
    }

    nuevo->sig = actual->sig;
    actual->sig = nuevo;
}

bool ColaEventos::hayEventoListo(float tiempoActual) const {
    return inicio != nullptr && inicio->tiempoDisparo <= tiempoActual;
}

TipoEvento ColaEventos::extraerProximo() {
    NodoEvento* victima = inicio;
    TipoEvento tipo = victima->tipo;

    inicio = inicio->sig;
    delete victima;

    return tipo;
}