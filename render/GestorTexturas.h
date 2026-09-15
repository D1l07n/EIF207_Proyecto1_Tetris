#pragma once
#include <SFML/Graphics.hpp>
#include "../core/TipoPieza.h"

class GestorTexturas {
public:
    GestorTexturas();

    const sf::Texture& obtenerTextura(TipoPieza tipo) const;
    const sf::Texture& obtenerTexturaDorada() const;
    const sf::Texture& obtenerTexturaCeldaVacia() const;
    const sf::Texture& obtenerTexturaMenu() const;
    const sf::Texture& obtenerTexturaRanking() const;

private:
    sf::Texture texturas[CANTIDAD_TIPOS_PIEZA];
    sf::Texture texturaDorada;
    sf::Texture texturaFondoTablero;
    sf::Texture texturaMenu;
    sf::Texture texturaRanking;
};
