#pragma once
#include <SFML/Graphics.hpp>
#include "../core/TipoPieza.h"

class GestorTexturas {
public:
    GestorTexturas();

    const sf::Texture& obtenerTextura(TipoPieza tipo) const;
    const sf::Texture& obtenerTexturaDorada() const;
    const sf::Texture& obtenerTexturaCeldaVacia() const;

private:
    sf::Texture texturas[CANTIDAD_TIPOS_PIEZA];
    sf::Texture texturaDorada;
    sf::Texture texturaFondoTablero;
};
