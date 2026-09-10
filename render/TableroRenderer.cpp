#include "TableroRenderer.h"
#include "ColorPieza.h"
#include "../config/Constants.h"

void TableroRenderer::dibujar(sf::RenderWindow& ventana, const Tablero& tablero) const {
    sf::RectangleShape celdaShape(sf::Vector2f(CELL_SIDE_SIZE - 1, CELL_SIDE_SIZE - 1));
 

    for (int fila = 0; fila < BOARD_ROWS; fila++) {
        for (int columna = 0; columna < BOARD_COLS; columna++) {
            int valor = tablero.getCelda(fila, columna);

            if (valor == CELDA_VACIA) {
                celdaShape.setFillColor(sf::Color(30, 30, 30)); // gris oscuro/celda vacia
            }
            else {
                TipoPieza tipo = static_cast<TipoPieza>(valor);
                celdaShape.setFillColor(obtenerColorPieza(tipo));
            }

            celdaShape.setPosition(
                static_cast<float>(columna * CELL_SIDE_SIZE),
                static_cast<float>(fila * CELL_SIDE_SIZE)
            );

            ventana.draw(celdaShape);
        }
    }
}