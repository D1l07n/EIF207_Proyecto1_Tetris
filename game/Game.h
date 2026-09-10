#pragma once
#include <SFML/Graphics.hpp>
#include "../core/Tablero.h"
#include "../core/ColaPiezas.h"
#include "../core/PilaHold.h"
#include "../core/ListaDobleReplay.h"
#include "../core/TipoMovimiento.h"
#include "../core/Pieza.h"
#include "../core/Colision.h"
#include "../render/TableroRenderer.h"
#include "../render/PiezaRenderer.h"

class Game {
public:
    Game();

    void procesarEventos(sf::RenderWindow& ventana);
    void actualizar();
    void dibujar(sf::RenderWindow& ventana);

private:
    Tablero tablero;
    ColaPiezas colaPiezas;
    PilaHold pilaHold;
    ListaDobleReplay historial;
    Pieza piezaActual;

    TableroRenderer tableroRenderer;
    PiezaRenderer piezaRenderer;

    sf::Clock relojCaida;
    sf::Clock relojRetrasoMovimiento;
    sf::Clock relojSoftDrop;

    bool esperandoRetrasoIzquierda;
    bool esperandoRetrasoDerecha;
    bool juegoTerminado;

    void generarNuevaPieza();
    void despuesDeFijar();
    void fijarYAvanzar();
    void moverPieza(int deltaColumna, bool& esperandoRetraso);
    void ejecutarHold();
    void deshacer();
    void rehacer();
};