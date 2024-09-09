#include "Bala.h"
#include <cmath>

#include "Bala.h"

Bala::Bala(const sf::Vector2f& position, float rotation)  : murio( false) {
    _texture.loadFromFile("bala.jpg");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
    _sprite.setPosition(position);
    _sprite.setRotation(rotation);

    float angleRad = (rotation - 90) * (3.14 / 180); // Convertir la rotación a radianes
    _velocidad = sf::Vector2f(cos(angleRad) * 5.0f, sin(angleRad) * 5.0f);
}

void Bala::update() {
    _sprite.move(_velocidad);
}

sf::FloatRect Bala::getBounds() const {
    return _sprite.getGlobalBounds();
}

void Bala::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}
