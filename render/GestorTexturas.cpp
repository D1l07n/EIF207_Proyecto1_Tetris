#include "GestorTexturas.h"
#include <cstdio>

GestorTexturas::GestorTexturas() {
    const char* rutas[CANTIDAD_TIPOS_PIEZA] = {
        "assets/cyan.png",     // I
        "assets/amarillo.png", // O
        "assets/morado.png",   // T
        "assets/verde.png",    // S
        "assets/rojo.png",     // Z
        "assets/azul.png",     // J
        "assets/naranja.png"   // L
    };

    for (int i = 0; i < CANTIDAD_TIPOS_PIEZA; i++) {
        if (!texturas[i].loadFromFile(rutas[i])) {
            printf("No se pudo cargar la textura: %s\n", rutas[i]);
        }
    }

    if (!texturaDorada.loadFromFile("assets/dorado.png")) {
        printf("No se pudo cargar assets/dorado.png\n");
    }

    if (!texturaFondoTablero.loadFromFile("assets/tablero.png")) {
        printf("No se pudo cargar assets/tablero.png\n");
    }
}

const sf::Texture& GestorTexturas::obtenerTextura(TipoPieza tipo) const {
    return texturas[static_cast<int>(tipo)];
}

const sf::Texture& GestorTexturas::obtenerTexturaDorada() const {
    return texturaDorada;
}

const sf::Texture& GestorTexturas::obtenerTexturaCeldaVacia() const {
    return texturaFondoTablero;
}