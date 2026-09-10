#pragma once
#include "TipoPieza.h"

struct Coordenada {
    int fila;
    int columna;
};

class Pieza {
public:
    explicit Pieza(TipoPieza tipoInicial);

    TipoPieza getTipo() const;
    int getOrientacion() const;
    int getFila() const;
    int getColumna() const;

    
    void setPosicion(int fila, int columna);
    void mover(int deltaFila, int deltaColumna);

   
    void obtenerCeldas(Coordenada celdas[4]) const;

   
    void obtenerCeldasSiRota(Coordenada celdas[4]) const;

   
    void rotar();

private:
    TipoPieza tipo;
    int orientacion; 
    int filaBase;
    int columnaBase;

   
    static const Coordenada FORMAS[CANTIDAD_TIPOS_PIEZA][4][4];

    void llenarCeldas(int orientacionUsada, Coordenada celdas[4]) const;
};
