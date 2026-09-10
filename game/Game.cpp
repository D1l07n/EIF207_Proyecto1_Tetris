#include "Game.h"
#include "../config/Constants.h"

Game::Game()
    : piezaActual(colaPiezas.desencolar()), juegoTerminado(false),
    esperandoRetrasoIzquierda(true), esperandoRetrasoDerecha(true)
{
    piezaActual.setPosicion(0, (BOARD_COLS / 2) - 2);
}

void Game::generarNuevaPieza() {
    TipoPieza tipo = colaPiezas.desencolar();
    piezaActual = Pieza(tipo);
    piezaActual.setPosicion(0, (BOARD_COLS / 2) - 2);

    if (Colision::esGameOver(piezaActual, tablero)) {
        juegoTerminado = true;
    }
}

void Game::despuesDeFijar() {
    tablero.limpiarLineasCompletas();
    generarNuevaPieza();
}

void Game::fijarYAvanzar() {
    tablero.fijarPieza(piezaActual);
    despuesDeFijar();
}

void Game::moverPieza(int deltaColumna, bool& esperandoRetraso) {
    float tiempoTranscurrido = relojRetrasoMovimiento.getElapsedTime().asSeconds();
    float limite = esperandoRetraso ? RETRASO_INICIAL_MOVIMIENTO : INTERVALO_MOVIMIENTO_LATERAL;

    if (tiempoTranscurrido >= limite) {
        Colision::moverSiEsPosible(piezaActual, tablero, 0, deltaColumna);
        relojRetrasoMovimiento.restart();
        esperandoRetraso = false; 
    }
}

void Game::procesarEventos(sf::RenderWindow& ventana) {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            ventana.close();
        }

        if (juegoTerminado) continue;

        if (evento.type == sf::Event::KeyPressed) {
          
            if (evento.key.code == sf::Keyboard::Left || evento.key.code == sf::Keyboard::A) {
                Colision::moverSiEsPosible(piezaActual, tablero, 0, -1);
                esperandoRetrasoIzquierda = true;
                relojRetrasoMovimiento.restart();
            }
            else if (evento.key.code == sf::Keyboard::Right || evento.key.code == sf::Keyboard::D) {
                Colision::moverSiEsPosible(piezaActual, tablero, 0, 1);
                esperandoRetrasoDerecha = true;
                relojRetrasoMovimiento.restart();
            }
            
            else if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::Q) {
                Colision::rotarSiEsPosible(piezaActual, tablero);
            }
            else if (evento.key.code == sf::Keyboard::Space) {
                Colision::hardDrop(piezaActual, tablero);
                despuesDeFijar();
            }
        }
    }
}

void Game::actualizar() {
    if (juegoTerminado) return;

    bool izquierda = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool derecha = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    if (izquierda) {
        moverPieza(-1, esperandoRetrasoIzquierda);
    }
    else if (derecha) {
        moverPieza(1, esperandoRetrasoDerecha);
    }

    bool abajo = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    if (abajo && relojSoftDrop.getElapsedTime().asSeconds() >= INTERVALO_SOFT_DROP) {
        if (!Colision::moverSiEsPosible(piezaActual, tablero, 1, 0)) {
            fijarYAvanzar();
        }
        relojSoftDrop.restart();
        relojCaida.restart(); 
    }

    if (relojCaida.getElapsedTime().asSeconds() >= FALL_INTERVAL_INITIAL) {
        if (!Colision::moverSiEsPosible(piezaActual, tablero, 1, 0)) {
            fijarYAvanzar();
        }
        relojCaida.restart();
    }
}

void Game::dibujar(sf::RenderWindow& ventana) {
    tableroRenderer.dibujar(ventana, tablero);
    piezaRenderer.dibujar(ventana, piezaActual);
}