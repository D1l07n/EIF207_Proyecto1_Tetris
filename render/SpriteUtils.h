#pragma once
#include <SFML/Graphics.hpp>

inline void escalarSprite(sf::Sprite& sprite, const sf::Texture& textura, float tamanioDestino) {
    sf::Vector2u tamOriginal = textura.getSize();
    sprite.setScale(
        tamanioDestino / static_cast<float>(tamOriginal.x),
        tamanioDestino / static_cast<float>(tamOriginal.y)
    );
}
