#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../core/Tablero.h"
#include "../core/ColaPiezas.h"
#include "../core/PilaHold.h"
#include "../core/ListaDobleReplay.h"
#include "../core/TipoMovimiento.h"
#include "../core/ColaEventos.h"
#include "../core/TipoEvento.h"
#include "../core/TablaPuntajes.h"
#include "../core/Pieza.h"
#include "../core/Colision.h"
#include "../render/TableroRenderer.h"
#include "../render/PiezaRenderer.h"
#include "../render/HUD.h"
#include "../render/GestorTexturas.h"
#include "../render/PantallasRenderer.h"
#include "EstadoJuego.h"
#include "../core/Benchmark.h"

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
    TablaPuntajes tablaPuntajes;
    Pieza piezaActual;

    TableroRenderer tableroRenderer;
    PiezaRenderer piezaRenderer;
    HUD hud;
    GestorTexturas texturas;
    PantallasRenderer pantallas;
    sf::Font fuente;

    EstadoJuego estado;
    std::string nombreIngresado;
    bool reproduccionAutomatica;

    sf::Clock relojCaida;
    sf::Clock relojRetrasoMovimiento;
    sf::Clock relojSoftDrop;
    sf::Clock relojPartida;
    sf::Clock relojReproduccionAuto;

    bool esperandoRetrasoIzquierda;
    bool esperandoRetrasoDerecha;
    bool proximaPiezaDorada;
    bool proximaPiezaBomba;
    float finPuntosDobles;
    int puntaje;

    bool animandoBomba;
    TipoPieza tipoBombaAnimando;
    bool faseBlancaBomba;
    sf::Clock relojAnimacionBomba;
    sf::Clock relojParpadeoBomba;

    void continuarFlujoTrasFijar();
    void actualizarAnimacionBomba();

    void reiniciarPartida();
    void finalizarPartida();
    void generarNuevaPieza();
    void despuesDeFijar();
    void fijarYAvanzar();
    void moverPieza(int deltaColumna, bool& esperandoRetraso);
    void ejecutarHold();
    void procesarEventosProgramados();
    void aplicarEfectoEvento(TipoEvento tipo);
    void programarEventosIniciales();
    bool puntosDoblesActivos() const;
    int calcularPuntosPorLineas(int cantidadLineas) const;
    bool dentroDeBoton(float mouseX, float mouseY, float centroBotonY) const;

    void procesarEventosMenu(const sf::Event& evento, sf::RenderWindow& ventana);
    void procesarEventosJugando(const sf::Event& evento);
    void procesarEventosPausa(const sf::Event& evento);
    void procesarEventosGameOver(const sf::Event& evento);
    void procesarEventosIngresoNombre(const sf::Event& evento);
    void procesarEventosViendoTabla(const sf::Event& evento);
    void procesarEventosReplay(const sf::Event& evento);

    void actualizarJugando();
    void actualizarReplay();
};