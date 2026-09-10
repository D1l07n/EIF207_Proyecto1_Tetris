#pragma once
#include <SFML/Graphics.hpp>
#include "../core/Tablero.h"

class TableroRenderer {
public:
    void dibujar(sf::RenderWindow& ventana, const Tablero& tablero) const;
};
