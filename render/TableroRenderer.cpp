#include "TableroRenderer.h"
#include "SpriteUtils.h"
#include "../config/Constants.h"

void TableroRenderer::dibujar(sf::RenderWindow& ventana, const Tablero& tablero, const GestorTexturas& texturas) const {
    sf::Sprite celdaSprite;

    for (int fila = 0; fila < BOARD_ROWS; fila++) {
        for (int columna = 0; columna < BOARD_COLS; columna++) {
            int valor = tablero.getCelda(fila, columna);

            const sf::Texture& textura = (valor == CELDA_VACIA)
                ? texturas.obtenerTexturaCeldaVacia()
                : texturas.obtenerTextura(static_cast<TipoPieza>(valor));

            celdaSprite.setTexture(textura, true);
            escalarSprite(celdaSprite, textura, static_cast<float>(CELL_SIDE_SIZE));
            celdaSprite.setPosition(
                static_cast<float>(columna * CELL_SIDE_SIZE),
                static_cast<float>(fila * CELL_SIDE_SIZE)
            );
            ventana.draw(celdaSprite);

            sf::RectangleShape borde(sf::Vector2f(CELL_SIDE_SIZE, CELL_SIDE_SIZE));
            borde.setPosition(celdaSprite.getPosition());
            borde.setFillColor(sf::Color::Transparent);
            borde.setOutlineColor(sf::Color::Black);
            borde.setOutlineThickness(1.0f);
            ventana.draw(borde);
        }
    }
}