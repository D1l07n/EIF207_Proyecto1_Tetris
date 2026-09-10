#pragma once
#include <SFML/Graphics.hpp>
#include "../core/TipoPieza.h"

inline sf::Color obtenerColorPieza(TipoPieza tipo) {
    switch (tipo) {
    case TipoPieza::I: return sf::Color::Cyan;
    case TipoPieza::O: return sf::Color::Yellow;
    case TipoPieza::T: return sf::Color(160, 32, 240);  // morado
    case TipoPieza::S: return sf::Color::Green;
    case TipoPieza::Z: return sf::Color::Red;
    case TipoPieza::J: return sf::Color::Blue;
    case TipoPieza::L: return sf::Color(255, 165, 0);   // naranja
    default: return sf::Color::White;
    }
}
