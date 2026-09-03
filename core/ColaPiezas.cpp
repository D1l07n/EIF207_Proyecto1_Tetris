#include "ColaPiezas.h"
#include <cstdlib>
#include <ctime>

const int TAMANO_BOLSA = 7;
const int MINIMO_EN_COLA = 7;

ColaPiezas::ColaPiezas() : inicio(nullptr), final(nullptr), cantidadActual(0) {
    srand(static_cast<unsigned int>(time(nullptr)));
    generarYEncolarBolsa();
    generarYEncolarBolsa();
}

ColaPiezas::~ColaPiezas() {
    while (!isEmpty()) {
        desencolar();
    }
}

bool ColaPiezas::isEmpty() const {
    return inicio == nullptr;
}

void ColaPiezas::encolar(TipoPieza v) {
    Nodo* nuevo = new Nodo(v);

    if (isEmpty()) {
        inicio = nuevo;
        final = nuevo;
    }
    else {
        final->sig = nuevo;
        final = nuevo;
    }
    cantidadActual++;   
}

void ColaPiezas::generarYEncolarBolsa() {
    TipoPieza bolsa[TAMANO_BOLSA] = {
        TipoPieza::I, TipoPieza::O, TipoPieza::T,
        TipoPieza::S, TipoPieza::Z, TipoPieza::J, TipoPieza::L
    };

    for (int i = TAMANO_BOLSA - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        TipoPieza temp = bolsa[i];
        bolsa[i] = bolsa[j];
        bolsa[j] = temp;
    }

    for (int i = 0; i < TAMANO_BOLSA; i++) {
        encolar(bolsa[i]);
    }
}

TipoPieza ColaPiezas::desencolar() {
    Nodo* victima = inicio;
    TipoPieza valor = victima->dato;

    inicio = inicio->sig;
    if (inicio == nullptr) {
        final = nullptr;
    }
    delete victima;
    cantidadActual--;   

    if (cantidadActual < MINIMO_EN_COLA) {   // ya no hace falta recorrer nada
        generarYEncolarBolsa();
    }

    return valor;
}

TipoPieza ColaPiezas::verEnPosicion(int posicion) const {
    Nodo* actual = inicio;
    for (int i = 0; i < posicion; i++) {
        actual = actual->sig;
    }
    return actual->dato;
}