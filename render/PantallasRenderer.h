#pragma once
#include <SFML/Graphics.hpp>
#include "../core/TablaPuntajes.h"
#include "GestorTexturas.h"
#include <string>

class PantallasRenderer {
public:
    void dibujarMenu(sf::RenderWindow& ventana, const sf::Font& fuente, const GestorTexturas& texturas) const;
    void dibujarPausa(sf::RenderWindow& ventana, const sf::Font& fuente) const;
    void dibujarGameOver(sf::RenderWindow& ventana, const sf::Font& fuente, int puntajeFinal) const;
    void dibujarIngresoNombre(sf::RenderWindow& ventana, const sf::Font& fuente, const std::string& nombreActual) const;
    void dibujarTablaPuntajes(sf::RenderWindow& ventana, const sf::Font& fuente, const TablaPuntajes& tabla, const GestorTexturas& texturas) const;
    void dibujarIndicadorReplay(sf::RenderWindow& ventana, const sf::Font& fuente, bool automatico) const;

private:
    void dibujarTexto(sf::RenderWindow& ventana, const sf::Font& fuente, const std::string& texto,
        float x, float y, int tamanio, sf::Color color = sf::Color::White) const;
    void dibujarTextoCentrado(sf::RenderWindow& ventana, const sf::Font& fuente, const std::string& texto,
        float centroX, float centroY, int tamanio, sf::Color color = sf::Color::White) const;
    void dibujarFondoOscuro(sf::RenderWindow& ventana, int alpha) const;
};