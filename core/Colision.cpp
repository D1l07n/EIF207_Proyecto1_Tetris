#include "Colision.h"

namespace Colision {

    bool hayEspacio(const Pieza& pieza, const Tablero& tablero) {
        Coordenada celdas[4];
        pieza.obtenerCeldas(celdas);

        for (int i = 0; i < 4; i++) {
            if (tablero.celdaOcupada(celdas[i].fila, celdas[i].columna)) {
				return false; // fuera del tablero o celda ya ocupada verifica dos condiciones a la vez..........
            }
        }
        return true;
    }

    bool moverSiEsPosible(Pieza& pieza, const Tablero& tablero, int deltaFila, int deltaColumna) {
        pieza.mover(deltaFila, deltaColumna);

        if (hayEspacio(pieza, tablero)) {
            return true;
        }

        pieza.mover(-deltaFila, -deltaColumna);
        return false;
    }

    bool rotarSiEsPosible(Pieza& pieza, const Tablero& tablero) {
        Coordenada celdasFuturas[4];
        pieza.obtenerCeldasSiRota(celdasFuturas);

        for (int i = 0; i < 4; i++) {
            if (tablero.celdaOcupada(celdasFuturas[i].fila, celdasFuturas[i].columna)) {
                return false; 
            }
        }

        pieza.rotar();
        return true;
    }

    int hardDrop(Pieza& pieza, Tablero& tablero) {
        int filasCaidas = 0;

        while (moverSiEsPosible(pieza, tablero, 1, 0)) {
            filasCaidas++;
        }

        tablero.fijarPieza(pieza);
        return filasCaidas;
    }

    bool esGameOver(const Pieza& piezaNueva, const Tablero& tablero) {
        return !hayEspacio(piezaNueva, tablero);
    }

}