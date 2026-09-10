#pragma once
#include <SFML/Graphics.hpp>
#include "../core/Pieza.h"

class PiezaRenderer {
public:
    void dibujar(sf::RenderWindow& ventana, const Pieza& pieza) const;
};
