#include "Pieza.h"

const Coordenada Pieza::FORMAS[CANTIDAD_TIPOS_PIEZA][4][4] = {
    // I
    {
        {{1,0},{1,1},{1,2},{1,3}},
        {{0,2},{1,2},{2,2},{3,2}},
        {{2,0},{2,1},{2,2},{2,3}},
        {{0,1},{1,1},{2,1},{3,1}}
    },
    // O 
    {
        {{1,1},{1,2},{2,1},{2,2}},
        {{1,1},{1,2},{2,1},{2,2}},
        {{1,1},{1,2},{2,1},{2,2}},
        {{1,1},{1,2},{2,1},{2,2}}
    },
    // T
    {
        {{0,1},{1,0},{1,1},{1,2}},
        {{0,1},{1,1},{1,2},{2,1}},
        {{1,0},{1,1},{1,2},{2,1}},
        {{0,1},{1,0},{1,1},{2,1}}
    },
    // S
    {
        {{0,1},{0,2},{1,0},{1,1}},
        {{0,1},{1,1},{1,2},{2,2}},
        {{1,1},{1,2},{2,0},{2,1}},
        {{0,0},{1,0},{1,1},{2,1}}
    },
    // Z
    {
        {{0,0},{0,1},{1,1},{1,2}},
        {{0,2},{1,1},{1,2},{2,1}},
        {{1,0},{1,1},{2,1},{2,2}},
        {{0,1},{1,0},{1,1},{2,0}}
    },
    // J
    {
        {{0,0},{1,0},{1,1},{1,2}},
        {{0,1},{0,2},{1,1},{2,1}},
        {{1,0},{1,1},{1,2},{2,2}},
        {{0,1},{1,1},{2,0},{2,1}}
    },
    // L
    {
        {{0,2},{1,0},{1,1},{1,2}},
        {{0,1},{1,1},{2,1},{2,2}},
        {{1,0},{1,1},{1,2},{2,0}},
        {{0,0},{0,1},{1,1},{2,1}}
    }
};

Pieza::Pieza(TipoPieza tipoInicial)
    : tipo(tipoInicial), orientacion(0), filaBase(0), columnaBase(0) {
}

TipoPieza Pieza::getTipo() const { return tipo; }
int Pieza::getOrientacion() const { return orientacion; }
int Pieza::getFila() const { return filaBase; }
int Pieza::getColumna() const { return columnaBase; }

void Pieza::setPosicion(int fila, int columna) {
    filaBase = fila;
    columnaBase = columna;
}

void Pieza::mover(int deltaFila, int deltaColumna) {
    filaBase += deltaFila;
    columnaBase += deltaColumna;
}

void Pieza::llenarCeldas(int orientacionUsada, Coordenada celdas[4]) const {
    int indiceTipo = static_cast<int>(tipo);
    for (int i = 0; i < 4; i++) {
        const Coordenada& offset = FORMAS[indiceTipo][orientacionUsada][i];
        celdas[i].fila = filaBase + offset.fila;
        celdas[i].columna = columnaBase + offset.columna;
    }
}

void Pieza::obtenerCeldas(Coordenada celdas[4]) const {
    llenarCeldas(orientacion, celdas);
}

void Pieza::obtenerCeldasSiRota(Coordenada celdas[4]) const {
    int siguienteOrientacion = (orientacion + 1) % 4;
    llenarCeldas(siguienteOrientacion, celdas);
}

void Pieza::rotar() {
    orientacion = (orientacion + 1) % 4;
}

void Pieza::marcarDorada() { dorada = true; }
void Pieza::marcarBomba() { bomba = true; }
bool Pieza::esPiezaDorada() const { return dorada; }
bool Pieza::esPiezaBomba() const { return bomba; }