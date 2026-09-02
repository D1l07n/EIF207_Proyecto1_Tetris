#include <SFML/Graphics.hpp>
#include "config/Constants.h"

int main() {
    sf::RenderWindow ventana(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        WINDOW_TITLE
    );
    ventana.setFramerateLimit(FPS);

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
        }

        ventana.clear(sf::Color::Black);
        ventana.display();
    }

    return 0;
}