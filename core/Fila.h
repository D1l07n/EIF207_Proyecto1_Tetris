#pragma once
#include "../config/Constants.h"

struct Fila {
    int celdas[BOARD_COLS];
    Fila* sig;

    Fila() : sig(nullptr) {
        for (int i = 0; i < BOARD_COLS; i++) {
            celdas[i] = CELDA_VACIA;
        }
    }

    bool estaCompleta() const {
        for (int i = 0; i < BOARD_COLS; i++) {
            if (celdas[i] == CELDA_VACIA) return false;
        }
        return true;
    }

    bool estaVacia() const {
        for (int i = 0; i < BOARD_COLS; i++) {
            if (celdas[i] != CELDA_VACIA) return false;
        }
        return true;
    }
};
