#include <SFML/Graphics.hpp>
#include "config/Constants.h"
#include "game/Game.h"


int main() {
    sf::RenderWindow ventana(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        WINDOW_TITLE,
        sf::Style::Titlebar | sf::Style::Close
    );
    ventana.setFramerateLimit(FPS);

    Game game;

    while (ventana.isOpen()) {
        game.procesarEventos(ventana);
        game.actualizar();

        ventana.clear(sf::Color::Black);
        game.dibujar(ventana);
        ventana.display();
    }

    return 0;
}