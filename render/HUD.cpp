#include "HUD.h"
#include "SpriteUtils.h"
#include "../core/Pieza.h"
#include "../config/Constants.h"
#include <string>


void HUD::dibujarPiezaMini(sf::RenderWindow& ventana, TipoPieza tipo, float posX, float posY,
    int columnaMinima, const GestorTexturas& texturas) const {
    Pieza piezaTemporal(tipo);
    piezaTemporal.setPosicion(0, 0);

    Coordenada celdas[4];
    piezaTemporal.obtenerCeldas(celdas);

    const sf::Texture& textura = texturas.obtenerTextura(tipo);
    sf::Sprite sprite;
    sprite.setTexture(textura, true);
    escalarSprite(sprite, textura, static_cast<float>(HUD_CELL_SIDE_SIZE));

    for (int i = 0; i < 4; i++) {
        int columnaAjustada = celdas[i].columna - columnaMinima;
        sprite.setPosition(
            posX + columnaAjustada * HUD_CELL_SIDE_SIZE,
            posY + celdas[i].fila * HUD_CELL_SIDE_SIZE
        );
        ventana.draw(sprite);

        sf::RectangleShape borde(sf::Vector2f(HUD_CELL_SIDE_SIZE, HUD_CELL_SIDE_SIZE));
        borde.setPosition(sprite.getPosition());
        borde.setFillColor(sf::Color::Transparent);
        borde.setOutlineColor(sf::Color::Black);
        borde.setOutlineThickness(1.0f);
        ventana.draw(borde);
    }
}

void HUD::dibujar(sf::RenderWindow& ventana, const sf::Font& fuente,
    const ColaPiezas& colaPiezas, const PilaHold& pilaHold,
    int puntaje, bool puntosDoblesActivos,
    const GestorTexturas& texturas) const {

    float panelX = BOARD_WIDTH + HUD_MARGIN;
    float y = HUD_MARGIN;

    dibujarTexto(ventana, fuente, "HOLD", panelX, y);
    y += HUD_FONT_SIZE + 5;

    if (!pilaHold.isEmpty()) {
        int columnaMinima = 0;
        obtenerAnchoPieza(pilaHold.top(), columnaMinima);
        dibujarPiezaMini(ventana, pilaHold.top(), panelX, y, columnaMinima, texturas);
    }
    y += (4 * HUD_CELL_SIDE_SIZE) + 20;

    dibujarTexto(ventana, fuente, "SIGUIENTES", panelX, y);
    y += HUD_FONT_SIZE + 5;

    float xPreview = panelX;
    for (int i = 0; i < 3; i++) {
        TipoPieza tipo = colaPiezas.verEnPosicion(i);
        int columnaMinima = 0;
        int ancho = obtenerAnchoPieza(tipo, columnaMinima);
        dibujarPiezaMini(ventana, tipo, xPreview, y, columnaMinima, texturas);
        xPreview += (ancho * HUD_CELL_SIDE_SIZE) + 10;
    }
    y += (4 * HUD_CELL_SIDE_SIZE) + 20;

    dibujarTexto(ventana, fuente, "PUNTAJE", panelX, y);
    y += HUD_FONT_SIZE + 5;
    dibujarTexto(ventana, fuente, std::to_string(puntaje), panelX, y);
    y += HUD_FONT_SIZE + 15;

    if (puntosDoblesActivos) {
        dibujarTexto(ventana, fuente, "x2 ACTIVO", panelX, y, sf::Color::Yellow);
    }
}

void HUD::dibujarTexto(sf::RenderWindow& ventana, const sf::Font& fuente,
    const std::string& texto, float posX, float posY,
    sf::Color color) const {
    sf::Text textoSf;
    textoSf.setFont(fuente);
    textoSf.setString(texto);
    textoSf.setCharacterSize(HUD_FONT_SIZE);
    textoSf.setFillColor(color);
    textoSf.setPosition(posX, posY);
    ventana.draw(textoSf);
}

int HUD::obtenerAnchoPieza(TipoPieza tipo, int& columnaMinima) const {
    Pieza piezaTemporal(tipo);
    piezaTemporal.setPosicion(0, 0);

    Coordenada celdas[4];
    piezaTemporal.obtenerCeldas(celdas);

    int maxColumna = celdas[0].columna;
    int minColumna = celdas[0].columna;
    for (int i = 1; i < 4; i++) {
        if (celdas[i].columna > maxColumna) maxColumna = celdas[i].columna;
        if (celdas[i].columna < minColumna) minColumna = celdas[i].columna;
    }

    columnaMinima = minColumna;
    return (maxColumna - minColumna) + 1;
}