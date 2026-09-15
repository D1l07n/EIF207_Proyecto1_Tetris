#include "Game.h"
#include "../config/Constants.h"

Game::Game()
    : piezaActual(TipoPieza::T), estado(EstadoJuego::MENU), reproduccionAutomatica(true),
    esperandoRetrasoIzquierda(true), esperandoRetrasoDerecha(true),
    proximaPiezaDorada(false), proximaPiezaBomba(false),
    finPuntosDobles(-1.0f), puntaje(0)
{
    if (!fuente.loadFromFile("assets/let.ttf")) {
        printf("No se pudo cargar la fuente assets/let.ttf\n");
    }

    piezaActual.setPosicion(0, (BOARD_COLS / 2) - 2);
}

void Game::reiniciarPartida() {
    tablero.reiniciar();
    colaPiezas.reiniciar();
    pilaHold.reiniciar();
    historial.reiniciar();
    colaEventos.vaciar();

    piezaActual = Pieza(colaPiezas.desencolar());
    piezaActual.setPosicion(0, (BOARD_COLS / 2) - 2);
    historial.establecerEstadoInicial(piezaActual);

    puntaje = 0;
    proximaPiezaDorada = false;
    proximaPiezaBomba = false;
    finPuntosDobles = -1.0f;
    esperandoRetrasoIzquierda = true;
    esperandoRetrasoDerecha = true;

    programarEventosIniciales();

    relojCaida.restart();
    relojRetrasoMovimiento.restart();
    relojSoftDrop.restart();
    relojPartida.restart();

    estado = EstadoJuego::JUGANDO;
}

void Game::finalizarPartida() {
    if (tablaPuntajes.calificaParaTop10(puntaje)) {
        nombreIngresado = "";
        estado = EstadoJuego::INGRESANDO_NOMBRE;
    }
    else {
        estado = EstadoJuego::GAME_OVER;
    }
}

void Game::programarEventosIniciales() {
    colaEventos.insertar(TipoEvento::PIEZA_DORADA, TIEMPO_EVENTO_DORADA_INICIAL);
    colaEventos.insertar(TipoEvento::PIEZA_BOMBA, TIEMPO_EVENTO_BOMBA_INICIAL);
    colaEventos.insertar(TipoEvento::PUNTOS_DOBLES, TIEMPO_EVENTO_PUNTOS_DOBLES_INICIAL);
}

void Game::generarNuevaPieza() {
    TipoPieza tipo = colaPiezas.desencolar();
    piezaActual = Pieza(tipo);
    piezaActual.setPosicion(0, (BOARD_COLS / 2) - 2);

    if (proximaPiezaDorada) {
        piezaActual.marcarDorada();
        proximaPiezaDorada = false;
    }
    else if (proximaPiezaBomba) {
        piezaActual.marcarBomba();
        proximaPiezaBomba = false;
    }

    if (Colision::esGameOver(piezaActual, tablero)) {
        finalizarPartida();
    }
}

int Game::calcularPuntosPorLineas(int cantidadLineas) const {
    switch (cantidadLineas) {
    case 1: return PUNTOS_1_LINEA;
    case 2: return PUNTOS_2_LINEAS;
    case 3: return PUNTOS_3_LINEAS;
    case 4: return PUNTOS_4_LINEAS;
    default: return 0;
    }
}

void Game::despuesDeFijar() {
    bool eraDorada = piezaActual.esPiezaDorada();

    if (piezaActual.esPiezaBomba()) {
        tablero.eliminarCeldasDeTipo(piezaActual.getTipo());
    }

    int lineasLimpiadas = tablero.limpiarLineasCompletas();

    if (lineasLimpiadas > 0) {
        int puntos = calcularPuntosPorLineas(lineasLimpiadas);
        if (eraDorada) puntos += PUNTOS_BONUS_DORADA;
        if (puntosDoblesActivos()) puntos *= 2;
        puntaje += puntos;
    }

    historial.registrarMovimiento(TipoMovimiento::COLOCAR, piezaActual, &tablero);
    procesarEventosProgramados();
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
        bool seMovio = Colision::moverSiEsPosible(piezaActual, tablero, 0, deltaColumna);
        if (seMovio) {
            TipoMovimiento tipo = (deltaColumna < 0) ? TipoMovimiento::MOVER_IZQUIERDA : TipoMovimiento::MOVER_DERECHA;
            historial.registrarMovimiento(tipo, piezaActual, nullptr);
        }
        relojRetrasoMovimiento.restart();
        esperandoRetraso = false;
    }
}

void Game::ejecutarHold() {
    if (pilaHold.isEmpty()) {
        pilaHold.push(piezaActual.getTipo());
        generarNuevaPieza();
    }
    else {
        TipoPieza guardada = pilaHold.pop();
        pilaHold.push(piezaActual.getTipo());
        piezaActual = Pieza(guardada);
        piezaActual.setPosicion(0, (BOARD_COLS / 2) - 2);

        if (Colision::esGameOver(piezaActual, tablero)) {
            finalizarPartida();
        }
    }
}

bool Game::puntosDoblesActivos() const {
    return finPuntosDobles >= 0.0f && relojPartida.getElapsedTime().asSeconds() < finPuntosDobles;
}

void Game::aplicarEfectoEvento(TipoEvento tipo) {
    float tiempoActual = relojPartida.getElapsedTime().asSeconds();

    switch (tipo) {
    case TipoEvento::PIEZA_DORADA:
        proximaPiezaDorada = true;
        colaEventos.insertar(TipoEvento::PIEZA_DORADA, tiempoActual + TIEMPO_EVENTO_DORADA_REPETICION);
        break;
    case TipoEvento::PIEZA_BOMBA:
        proximaPiezaBomba = true;
        colaEventos.insertar(TipoEvento::PIEZA_BOMBA, tiempoActual + TIEMPO_EVENTO_BOMBA_REPETICION);
        break;
    case TipoEvento::PUNTOS_DOBLES:
        finPuntosDobles = tiempoActual + DURACION_PUNTOS_DOBLES;
        colaEventos.insertar(TipoEvento::PUNTOS_DOBLES, tiempoActual + TIEMPO_EVENTO_PUNTOS_DOBLES_REPETICION);
        break;
    }
}

void Game::procesarEventosProgramados() {
    float tiempoActual = relojPartida.getElapsedTime().asSeconds();
    while (!colaEventos.isEmpty() && colaEventos.hayEventoListo(tiempoActual)) {
        aplicarEfectoEvento(colaEventos.extraerProximo());
    }
}



bool Game::dentroDeBoton(float mouseX, float mouseY, float centroBotonY) const {
    float izquierda = BOTON_CENTRO_X - BOTON_ANCHO / 2.0f;
    float derecha = BOTON_CENTRO_X + BOTON_ANCHO / 2.0f;
    float arriba = centroBotonY - BOTON_ALTO / 2.0f;
    float abajo = centroBotonY + BOTON_ALTO / 2.0f;

    return mouseX >= izquierda && mouseX <= derecha
        && mouseY >= arriba && mouseY <= abajo;
}

void Game::procesarEventosMenu(const sf::Event& evento, sf::RenderWindow& ventana) {
    if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::Enter) {
            reiniciarPartida();
        }
        else if (evento.key.code == sf::Keyboard::T) {
            estado = EstadoJuego::VIENDO_TABLA;
        }
    }
    else if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
        float mx = static_cast<float>(evento.mouseButton.x);
        float my = static_cast<float>(evento.mouseButton.y);

        if (dentroDeBoton(mx, my, BOTON_JUGAR_CENTRO_Y)) {
            reiniciarPartida();
        }
        else if (dentroDeBoton(mx, my, BOTON_PUNTAJES_CENTRO_Y)) {
            estado = EstadoJuego::VIENDO_TABLA;
        }
        else if (dentroDeBoton(mx, my, BOTON_SALIR_CENTRO_Y)) {
            ventana.close();
        }
    }
}

void Game::procesarEventosJugando(const sf::Event& evento) {
    if (evento.type != sf::Event::KeyPressed) return;

    if (evento.key.code == sf::Keyboard::Left || evento.key.code == sf::Keyboard::A) {
        bool seMovio = Colision::moverSiEsPosible(piezaActual, tablero, 0, -1);
        if (seMovio) historial.registrarMovimiento(TipoMovimiento::MOVER_IZQUIERDA, piezaActual, nullptr);
        esperandoRetrasoIzquierda = true;
        relojRetrasoMovimiento.restart();
    }
    else if (evento.key.code == sf::Keyboard::Right || evento.key.code == sf::Keyboard::D) {
        bool seMovio = Colision::moverSiEsPosible(piezaActual, tablero, 0, 1);
        if (seMovio) historial.registrarMovimiento(TipoMovimiento::MOVER_DERECHA, piezaActual, nullptr);
        esperandoRetrasoDerecha = true;
        relojRetrasoMovimiento.restart();
    }
    else if (evento.key.code == sf::Keyboard::Up || evento.key.code == sf::Keyboard::Q) {
        bool roto = Colision::rotarSiEsPosible(piezaActual, tablero);
        if (roto) historial.registrarMovimiento(TipoMovimiento::ROTAR, piezaActual, nullptr);
    }
    else if (evento.key.code == sf::Keyboard::Space) {
        Colision::hardDrop(piezaActual, tablero);
        despuesDeFijar();
    }
    else if (evento.key.code == sf::Keyboard::C) {
        ejecutarHold();
    }
    else if (evento.key.code == sf::Keyboard::Z) {
        historial.deshacer(piezaActual, tablero);
    }
    else if (evento.key.code == sf::Keyboard::X) {
        historial.rehacer(piezaActual, tablero);
    }
    else if (evento.key.code == sf::Keyboard::P) {
        estado = EstadoJuego::PAUSA;
    }
    else if (evento.key.code == sf::Keyboard::Escape) {
        estado = EstadoJuego::MENU;
    }
}

void Game::procesarEventosPausa(const sf::Event& evento) {
    if (evento.type != sf::Event::KeyPressed) return;

    if (evento.key.code == sf::Keyboard::P) {
        estado = EstadoJuego::JUGANDO;
        relojCaida.restart();
        relojRetrasoMovimiento.restart();
        relojSoftDrop.restart();
    }
    else if (evento.key.code == sf::Keyboard::Escape) {
        estado = EstadoJuego::MENU;
    }
}

void Game::procesarEventosGameOver(const sf::Event& evento) {
    if (evento.type != sf::Event::KeyPressed) return;

    if (evento.key.code == sf::Keyboard::Enter) {
        estado = EstadoJuego::MENU;
    }
    else if (evento.key.code == sf::Keyboard::R) {
        historial.irAlPrimero(piezaActual, tablero);
        reproduccionAutomatica = true;
        relojReproduccionAuto.restart();
        estado = EstadoJuego::REPRODUCIENDO_REPLAY;
    }
}

void Game::procesarEventosIngresoNombre(const sf::Event& evento) {
    if (evento.type == sf::Event::TextEntered) {
        unsigned int codigo = evento.text.unicode;
        if (codigo >= 32 && codigo < 127 && nombreIngresado.length() < MAX_LARGO_NOMBRE) {
            nombreIngresado += static_cast<char>(codigo);
        }
    }
    else if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::BackSpace && !nombreIngresado.empty()) {
            nombreIngresado.pop_back();
        }
        else if (evento.key.code == sf::Keyboard::Enter && !nombreIngresado.empty()) {
            tablaPuntajes.insertar(nombreIngresado, puntaje);
            estado = EstadoJuego::GAME_OVER;
        }
    }
}

void Game::procesarEventosViendoTabla(const sf::Event& evento) {
    if (evento.type != sf::Event::KeyPressed) return;

    if (evento.key.code == sf::Keyboard::Escape) {
        estado = EstadoJuego::MENU;
    }
}

void Game::procesarEventosReplay(const sf::Event& evento) {
    if (evento.type != sf::Event::KeyPressed) return;

    if (evento.key.code == sf::Keyboard::Space) {
        reproduccionAutomatica = !reproduccionAutomatica;
        relojReproduccionAuto.restart();
    }
    else if (!reproduccionAutomatica && evento.key.code == sf::Keyboard::Right) {
        historial.rehacer(piezaActual, tablero);
    }
    else if (!reproduccionAutomatica && evento.key.code == sf::Keyboard::Left) {
        historial.deshacer(piezaActual, tablero);
    }
    else if (evento.key.code == sf::Keyboard::Escape) {
        estado = EstadoJuego::MENU;
    }
}

void Game::procesarEventos(sf::RenderWindow& ventana) {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            ventana.close();
            continue;
        }

        if (estado == EstadoJuego::MENU && evento.type == sf::Event::KeyPressed
            && evento.key.code == sf::Keyboard::Escape) {
            ventana.close();
            continue;
        }

        switch (estado) {
        case EstadoJuego::MENU: procesarEventosMenu(evento, ventana); break;
        case EstadoJuego::JUGANDO: procesarEventosJugando(evento); break;
        case EstadoJuego::PAUSA: procesarEventosPausa(evento); break;
        case EstadoJuego::GAME_OVER: procesarEventosGameOver(evento); break;
        case EstadoJuego::INGRESANDO_NOMBRE: procesarEventosIngresoNombre(evento); break;
        case EstadoJuego::VIENDO_TABLA: procesarEventosViendoTabla(evento); break;
        case EstadoJuego::REPRODUCIENDO_REPLAY: procesarEventosReplay(evento); break;
        }
    }
}



void Game::actualizarJugando() {
    procesarEventosProgramados();

    bool izquierda = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool derecha = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    if (izquierda) moverPieza(-1, esperandoRetrasoIzquierda);
    else if (derecha) moverPieza(1, esperandoRetrasoDerecha);

    bool abajo = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    if (abajo && relojSoftDrop.getElapsedTime().asSeconds() >= INTERVALO_SOFT_DROP) {
        bool bajo = Colision::moverSiEsPosible(piezaActual, tablero, 1, 0);
        if (bajo) historial.registrarMovimiento(TipoMovimiento::BAJAR, piezaActual, nullptr);
        else fijarYAvanzar();
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

void Game::actualizarReplay() {
    if (!reproduccionAutomatica) return;

    if (relojReproduccionAuto.getElapsedTime().asSeconds() >= INTERVALO_REPRODUCCION_AUTO) {
        bool avanzo = historial.rehacer(piezaActual, tablero);
        relojReproduccionAuto.restart();
        if (!avanzo) {
            reproduccionAutomatica = false;
        }
    }
}

void Game::actualizar() {
    switch (estado) {
    case EstadoJuego::JUGANDO: actualizarJugando(); break;
    case EstadoJuego::REPRODUCIENDO_REPLAY: actualizarReplay(); break;
    default: break;
    }
}

// ---------- DIBUJAR ----------

void Game::dibujar(sf::RenderWindow& ventana) {
    switch (estado) {
    case EstadoJuego::MENU:
        pantallas.dibujarMenu(ventana, fuente, texturas);
        break;

    case EstadoJuego::JUGANDO:
        tableroRenderer.dibujar(ventana, tablero, texturas);
        piezaRenderer.dibujar(ventana, piezaActual, texturas);
        hud.dibujar(ventana, fuente, colaPiezas, pilaHold, puntaje, puntosDoblesActivos(), texturas);
        break;

    case EstadoJuego::PAUSA:
        tableroRenderer.dibujar(ventana, tablero, texturas);
        piezaRenderer.dibujar(ventana, piezaActual, texturas);
        hud.dibujar(ventana, fuente, colaPiezas, pilaHold, puntaje, puntosDoblesActivos(), texturas);
        pantallas.dibujarPausa(ventana, fuente);
        break;

    case EstadoJuego::GAME_OVER:
        pantallas.dibujarGameOver(ventana, fuente, puntaje);
        break;

    case EstadoJuego::INGRESANDO_NOMBRE:
        pantallas.dibujarIngresoNombre(ventana, fuente, nombreIngresado);
        break;

    case EstadoJuego::VIENDO_TABLA:
        pantallas.dibujarTablaPuntajes(ventana, fuente, tablaPuntajes, texturas);
        break;

    case EstadoJuego::REPRODUCIENDO_REPLAY:
        tableroRenderer.dibujar(ventana, tablero, texturas);
        piezaRenderer.dibujar(ventana, piezaActual, texturas);
        pantallas.dibujarIndicadorReplay(ventana, fuente, reproduccionAutomatica);
        break;
    }
}