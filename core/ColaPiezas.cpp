#include "ColaPiezas.h"
#include "../config/Constants.h"
#include <cstdlib>
#include <ctime>


ColaPiezas::ColaPiezas() : inicio(nullptr), final(nullptr), cantidadActual(0) {
    srand(static_cast<unsigned int>(time(nullptr)));
    generarYEncolarBolsa();
    generarYEncolarBolsa();
}

void ColaPiezas::vaciarNodos() {
    Nodo* actual = inicio;
    while (actual != nullptr) {
        Nodo* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
    inicio = nullptr;
    final = nullptr;
    cantidadActual = 0;
}

ColaPiezas::~ColaPiezas() {
    vaciarNodos(); 
}

void ColaPiezas::reiniciar() {
    vaciarNodos();
    generarYEncolarBolsa();
    generarYEncolarBolsa();
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
    TipoPieza bolsa[CANTIDAD_TIPOS_PIEZA] = {
        TipoPieza::I, TipoPieza::O, TipoPieza::T,
        TipoPieza::S, TipoPieza::Z, TipoPieza::J, TipoPieza::L
    };

    for (int i = CANTIDAD_TIPOS_PIEZA - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        TipoPieza temp = bolsa[i];
        bolsa[i] = bolsa[j];
        bolsa[j] = temp;
    }

    for (int i = 0; i < CANTIDAD_TIPOS_PIEZA; i++) {
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

    if (cantidadActual < MINIMO_EN_COLA) {   
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