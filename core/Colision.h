#pragma once
#include "Pieza.h"
#include "Tablero.h"

namespace Colision {
   
    bool hayEspacio(const Pieza& pieza, const Tablero& tablero);

   
    bool moverSiEsPosible(Pieza& pieza, const Tablero& tablero, int deltaFila, int deltaColumna);

    
    bool rotarSiEsPosible(Pieza& pieza, const Tablero& tablero);

    
    int hardDrop(Pieza& pieza, Tablero& tablero);

   
    bool esGameOver(const Pieza& piezaNueva, const Tablero& tablero);
}
