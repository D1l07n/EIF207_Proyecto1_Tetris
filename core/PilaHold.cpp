#include "PilaHold.h"

PilaHold::PilaHold() : tope(nullptr) {
}

PilaHold::~PilaHold() {
    if (tope != nullptr) {
        delete tope;
    }
}

bool PilaHold::isEmpty() const {
    return tope == nullptr;
}

bool PilaHold::push(TipoPieza v) {
    if (tope != nullptr) {
        return false; 
    }
    tope = new Nodo(v);
    return true;
}

TipoPieza PilaHold::pop() {
    Nodo* victima = tope;
    TipoPieza valor = victima->dato;
    tope = nullptr; 
    delete victima;
    return valor;
}

TipoPieza PilaHold::top() const {
    return tope->dato;
}