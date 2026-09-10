#include "ListaDobleReplay.h"

ListaDobleReplay::ListaDobleReplay() : inicio(nullptr), fin(nullptr), actual(nullptr) {
}

ListaDobleReplay::~ListaDobleReplay() {
    eliminarDesde(inicio);
}

void ListaDobleReplay::eliminarDesde(NodoReplay* nodo) {
    while (nodo != nullptr) {
        NodoReplay* siguiente = nodo->sig;
        delete nodo;
        nodo = siguiente;
    }
}

bool ListaDobleReplay::hayHistorial() const {
    return inicio != nullptr;
}

void ListaDobleReplay::establecerEstadoInicial(const Pieza& piezaInicial) {
    tipoPiezaInicial = piezaInicial.getTipo();
    filaInicial = piezaInicial.getFila();
    columnaInicial = piezaInicial.getColumna();
    orientacionInicial = piezaInicial.getOrientacion();
}

void ListaDobleReplay::registrarMovimiento(TipoMovimiento tipo, const Pieza& pieza, const Tablero* tableroSiColocar) {
   
    if (actual != nullptr && actual->sig != nullptr) {
        eliminarDesde(actual->sig);
        actual->sig = nullptr;
        fin = actual;
    }
    else if (actual == nullptr && inicio != nullptr) {
        eliminarDesde(inicio);
        inicio = nullptr;
        fin = nullptr;
    }

    NodoReplay* nuevo = new NodoReplay();
    nuevo->tipo = tipo;
    nuevo->tipoPieza = pieza.getTipo();
    nuevo->orientacion = pieza.getOrientacion();
    nuevo->fila = pieza.getFila();
    nuevo->columna = pieza.getColumna();

    if (tipo == TipoMovimiento::COLOCAR && tableroSiColocar != nullptr) {
        nuevo->tieneSnapshotTablero = true;
        tableroSiColocar->copiarEstado(nuevo->snapshotTablero);
    }

    if (actual == nullptr) {
        inicio = nuevo;
        fin = nuevo;
    }
    else {
        nuevo->ant = actual;
        actual->sig = nuevo;
        fin = nuevo;
    }

    actual = nuevo;
}

void ListaDobleReplay::aplicarNodo(NodoReplay* nodo, Pieza& piezaActual, Tablero& tablero) const {
    Pieza reconstruida(nodo->tipoPieza);
    reconstruida.setPosicion(nodo->fila, nodo->columna);
    for (int i = 0; i < nodo->orientacion; i++) {
        reconstruida.rotar();
    }
    piezaActual = reconstruida;

    if (nodo->tieneSnapshotTablero) {
        tablero.restaurarEstado(nodo->snapshotTablero);
    }
}

bool ListaDobleReplay::deshacer(Pieza& piezaActual, Tablero& tablero) {//...
    if (actual == nullptr) {
        return false; 
    }

    bool actualEraColocar = actual->tieneSnapshotTablero;
    NodoReplay* nodoAnterior = actual->ant;

    
        
        if (nodoAnterior == nullptr) {
            if (actualEraColocar) {
                tablero.reiniciar();
            }

            Pieza reconstruida(tipoPiezaInicial);
            reconstruida.setPosicion(filaInicial, columnaInicial);
            for (int i = 0; i < orientacionInicial; i++) {
                reconstruida.rotar();
            }
            piezaActual = reconstruida; 

            actual = nullptr;
            return true;
        }
    


    Pieza reconstruida(nodoAnterior->tipoPieza);
    reconstruida.setPosicion(nodoAnterior->fila, nodoAnterior->columna);
    for (int i = 0; i < nodoAnterior->orientacion; i++) {
        reconstruida.rotar();
    }
    piezaActual = reconstruida;

    
    if (actualEraColocar) {
        NodoReplay* p = nodoAnterior;
        while (p != nullptr && !p->tieneSnapshotTablero) {
            p = p->ant;
        }
        if (p != nullptr) {
            tablero.restaurarEstado(p->snapshotTablero);
        }
        else {
            tablero.reiniciar();
        }
    }

    actual = nodoAnterior;
    return true;
}

bool ListaDobleReplay::rehacer(Pieza& piezaActual, Tablero& tablero) {
    NodoReplay* siguiente = (actual == nullptr) ? inicio : actual->sig;

    if (siguiente == nullptr) {
        return false; 
    }

    aplicarNodo(siguiente, piezaActual, tablero);
    actual = siguiente;
    return true;
}

void ListaDobleReplay::irAlPrimero() {
    actual = nullptr;
}

bool ListaDobleReplay::avanzarReproduccion(Pieza& piezaActual, Tablero& tablero) {
    return rehacer(piezaActual, tablero); 
}