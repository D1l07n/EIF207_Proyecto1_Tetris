#pragma once
#include <SFML/Graphics.hpp>
#include "../core/Tablero.h"
#include "../core/ColaPiezas.h"
#include "../core/PilaHold.h"
#include "../core/ListaDobleReplay.h"
#include "../core/TipoMovimiento.h"
#include "../core/ColaEventos.h"
#include "../core/TipoEvento.h"
#include "../core/Pieza.h"
#include "../core/Colision.h"
#include "../render/TableroRenderer.h"
#include "../render/PiezaRenderer.h"
#include "../render/HUD.h"
#include "../render/GestorTexturas.h"

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
    ColaEventos colaEventos;
    Pieza piezaActual;

    TableroRenderer tableroRenderer;
    PiezaRenderer piezaRenderer;
    HUD hud;
    sf::Font fuente;

    GestorTexturas texturas;

    sf::Clock relojCaida;
    sf::Clock relojRetrasoMovimiento;
    sf::Clock relojSoftDrop;
    sf::Clock relojPartida; 

    bool esperandoRetrasoIzquierda;
    bool esperandoRetrasoDerecha;
    bool proximaPiezaDorada;
    bool proximaPiezaBomba;
    bool juegoTerminado;
    int puntaje;
    float finPuntosDobles;

    void generarNuevaPieza();
    void despuesDeFijar();
    void fijarYAvanzar();
    void moverPieza(int deltaColumna, bool& esperandoRetraso);
    void ejecutarHold();
    void deshacer();
    void rehacer();
    void procesarEventosProgramados();
    void aplicarEfectoEvento(TipoEvento tipo);
    void programarEventosIniciales();
    bool puntosDoblesActivos() const;
    int calcularPuntosPorLineas(int cantidadLineas) const;
};