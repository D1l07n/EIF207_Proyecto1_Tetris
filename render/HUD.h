#pragma once
#include <SFML/Graphics.hpp>
#include "../core/ColaPiezas.h"
#include "../core/PilaHold.h"
#include "../core/TipoPieza.h"
#include "GestorTexturas.h"

class HUD {
public:
    void dibujar(sf::RenderWindow& ventana, const sf::Font& fuente,
        const ColaPiezas& colaPiezas, const PilaHold& pilaHold,
        int puntaje, bool puntosDoblesActivos,
        const GestorTexturas& texturas) const;

private:
    void dibujarPiezaMini(sf::RenderWindow& ventana, TipoPieza tipo, float posX, float posY,
        int columnaMinima, const GestorTexturas& texturas) const;
    
    int obtenerAnchoPieza(TipoPieza tipo, int& columnaMinima) const;

    void dibujarTexto(sf::RenderWindow& ventana, const sf::Font& fuente,
        const std::string& texto, float posX, float posY,
        sf::Color color = sf::Color::White) const;
};