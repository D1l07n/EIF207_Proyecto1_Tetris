#pragma once
#include "TipoMovimiento.h"
#include "TipoPieza.h"
#include "Pieza.h"
#include "Tablero.h"
#include "../config/Constants.h"

class ListaDobleReplay {
public:
    ListaDobleReplay();
    ~ListaDobleReplay();

    
    void registrarMovimiento(TipoMovimiento tipo, const Pieza& pieza, const Tablero* tableroSiColocar);

 
    bool deshacer(Pieza& piezaActual, Tablero& tablero);

   
    bool rehacer(Pieza& piezaActual, Tablero& tablero);

  
    void irAlPrimero();
    bool avanzarReproduccion(Pieza& piezaActual, Tablero& tablero);

    bool hayHistorial() const;

private:
    struct NodoReplay {
        TipoMovimiento tipo;
        TipoPieza tipoPieza;
        int orientacion;
        int fila;
        int columna;

        bool tieneSnapshotTablero;
        int snapshotTablero[BOARD_ROWS][BOARD_COLS];

        NodoReplay* ant;
        NodoReplay* sig;

        NodoReplay() : ant(nullptr), sig(nullptr), tieneSnapshotTablero(false) {}
    };

    NodoReplay* inicio;
    NodoReplay* fin;
    NodoReplay* actual; 

    void aplicarNodo(NodoReplay* nodo, Pieza& piezaActual, Tablero& tablero) const;
    void eliminarDesde(NodoReplay* nodo);
};
