#include "Tablero.h"

Tablero::Tablero() : inicio(nullptr) {
    
    for (int i = 0; i < BOARD_ROWS; i++) {
        Fila* nueva = new Fila();
        nueva->sig = inicio;
        inicio = nueva;
    }
}

Tablero::~Tablero() {
    Fila* actual = inicio;
    while (actual != nullptr) {
        Fila* siguiente = actual->sig;
        delete actual;
        actual = siguiente;
    }
}

Fila* Tablero::obtenerFila(int indice) const {
    Fila* actual = inicio;
    for (int i = 0; i < indice && actual != nullptr; i++) {
        actual = actual->sig;
    }
    return actual;
}

bool Tablero::dentroDelTablero(int fila, int columna) const {
    return fila >= 0 && fila < BOARD_ROWS && columna >= 0 && columna < BOARD_COLS;
}

bool Tablero::celdaOcupada(int fila, int columna) const {
    if (!dentroDelTablero(fila, columna)) return true; 
    Fila* f = obtenerFila(fila);
    return f->celdas[columna] != CELDA_VACIA;
}

int Tablero::getCelda(int fila, int columna) const {
    Fila* f = obtenerFila(fila);
    return f->celdas[columna];
}

void Tablero::fijarPieza(const Pieza& p) {
    Coordenada celdas[4];
    p.obtenerCeldas(celdas);

    int tipoComoInt = static_cast<int>(p.getTipo());
    for (int i = 0; i < 4; i++) {
        if (dentroDelTablero(celdas[i].fila, celdas[i].columna)) {
            Fila* f = obtenerFila(celdas[i].fila);
            f->celdas[celdas[i].columna] = tipoComoInt;
        }
    }
}

void Tablero::copiarEstado(int destino[BOARD_ROWS][BOARD_COLS]) const {
    Fila* actualFila = inicio;
    for (int f = 0; f < BOARD_ROWS && actualFila != nullptr; f++) {
        for (int c = 0; c < BOARD_COLS; c++) {
            destino[f][c] = actualFila->celdas[c];
        }
        actualFila = actualFila->sig;
    }
}

void Tablero::restaurarEstado(const int origen[BOARD_ROWS][BOARD_COLS]) {
    Fila* actualFila = inicio;
    for (int f = 0; f < BOARD_ROWS && actualFila != nullptr; f++) {
        for (int c = 0; c < BOARD_COLS; c++) {
            actualFila->celdas[c] = origen[f][c];
        }
        actualFila = actualFila->sig;
    }
}

void Tablero::reiniciar() {
    Fila* actualFila = inicio;
    while (actualFila != nullptr) {
        for (int c = 0; c < BOARD_COLS; c++) {
            actualFila->celdas[c] = CELDA_VACIA;
        }
        actualFila = actualFila->sig;
    }
}

void Tablero::invertirFilas() {
    
    Fila* ant = nullptr;
    Fila* actualFila = inicio;

    while (actualFila != nullptr) {
        Fila* siguienteFila = actualFila->sig;
        actualFila->sig = ant;
        ant = actualFila;
        actualFila = siguienteFila;
    }

    inicio = ant;
}

void Tablero::eliminarCeldasDeTipo(TipoPieza tipo) {
    int tipoComoInt = static_cast<int>(tipo);
    Fila* actualFila = inicio;

    while (actualFila != nullptr) {
        for (int c = 0; c < BOARD_COLS; c++) {
            if (actualFila->celdas[c] == tipoComoInt) {
                actualFila->celdas[c] = CELDA_VACIA;
            }
        }
        actualFila = actualFila->sig;
    }
}

int Tablero::limpiarLineasCompletas() {
    
    int eliminadas = 0;
    Fila* actual = inicio;
    Fila* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->estaCompleta()) {
            Fila* victima = actual;

            if (anterior == nullptr) {
                inicio = actual->sig; // la victima era la primera fila
            }
            else {
                anterior->sig = actual->sig;
            }

            actual = actual->sig;
            delete victima;
            eliminadas++;
           
        }
        else {
            anterior = actual;
            actual = actual->sig;
        }
    }

    for (int i = 0; i < eliminadas; i++) {
        Fila* nueva = new Fila();
        nueva->sig = inicio;
        inicio = nueva;
    }

    return eliminadas;
}