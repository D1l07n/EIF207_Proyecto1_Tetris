#pragma once
#include <SFML/Graphics.hpp>
#include "../core/Tablero.h"
#include "../core/TipoPieza.h"
#include "GestorTexturas.h"

class TableroRenderer {
public:
    void dibujar(sf::RenderWindow& ventana, const Tablero& tablero, const GestorTexturas& texturas,
        bool animandoBomba = false, TipoPieza tipoAnimando = TipoPieza::I, bool mostrarBlanco = false) const;
};
