#pragma once
#include <SFML/Graphics.hpp>
#include "../core/Tablero.h"
#include "GestorTexturas.h"

class TableroRenderer {
public:
    void dibujar(sf::RenderWindow& ventana, const Tablero& tablero, const GestorTexturas& texturas) const;
};
