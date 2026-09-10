#include "PiezaRenderer.h"
#include "ColorPieza.h"
#include "../config/Constants.h"

void PiezaRenderer::dibujar(sf::RenderWindow& ventana, const Pieza& pieza) const {
    Coordenada celdas[4];
    pieza.obtenerCeldas(celdas);

    sf::RectangleShape celdaShape(sf::Vector2f(CELL_SIDE_SIZE - 1, CELL_SIDE_SIZE - 1));
    celdaShape.setFillColor(obtenerColorPieza(pieza.getTipo()));

    for (int i = 0; i < 4; i++) {
        if (celdas[i].fila < 0) continue;

        celdaShape.setPosition(
            static_cast<float>(celdas[i].columna * CELL_SIDE_SIZE),
            static_cast<float>(celdas[i].fila * CELL_SIDE_SIZE)
        );

        ventana.draw(celdaShape);
    }
}