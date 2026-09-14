#include "PiezaRenderer.h"
#include "SpriteUtils.h"
#include "../config/Constants.h"

void PiezaRenderer::dibujar(sf::RenderWindow& ventana, const Pieza& pieza, const GestorTexturas& texturas) const {
    Coordenada celdas[4];
    pieza.obtenerCeldas(celdas);

    const sf::Texture& textura = pieza.esPiezaDorada() ? texturas.obtenerTexturaDorada() : texturas.obtenerTextura(pieza.getTipo());

    sf::Sprite sprite;
    sprite.setTexture(textura, true);
    escalarSprite(sprite, textura, static_cast<float>(CELL_SIDE_SIZE));

    for (int i = 0; i < 4; i++) {
        if (celdas[i].fila < 0) continue;

        sprite.setPosition(
            static_cast<float>(celdas[i].columna * CELL_SIDE_SIZE),
            static_cast<float>(celdas[i].fila * CELL_SIDE_SIZE)
        );
        ventana.draw(sprite);

        sf::RectangleShape borde(sf::Vector2f(CELL_SIDE_SIZE, CELL_SIDE_SIZE));
        borde.setPosition(sprite.getPosition());
        borde.setFillColor(sf::Color::Transparent);
        borde.setOutlineColor(sf::Color::Black);
        borde.setOutlineThickness(1.0f);
        ventana.draw(borde);
    }
}