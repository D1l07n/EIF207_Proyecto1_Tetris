#pragma once
#include "Fila.h"
#include "Pieza.h"

class Tablero {
public:
    Tablero();
    ~Tablero();

    bool celdaOcupada(int fila, int columna) const;
    bool dentroDelTablero(int fila, int columna) const;

    
    void fijarPieza(const Pieza& p);

   
    int limpiarLineasCompletas();

    int getCelda(int fila, int columna) const;

private:
    Fila* inicio; 

    Fila* obtenerFila(int indice) const;
};
