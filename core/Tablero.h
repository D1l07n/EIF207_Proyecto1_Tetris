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

    void copiarEstado(int destino[BOARD_ROWS][BOARD_COLS]) const;

    void restaurarEstado(const int origen[BOARD_ROWS][BOARD_COLS]);

    void reiniciar(); 

    void invertirFilas();

    void eliminarCeldasDeTipo(TipoPieza tipo);

    int limpiarLineasCompletas();

    int getCelda(int fila, int columna) const;

private:
    Fila* inicio; 

    Fila* obtenerFila(int indice) const;
};
