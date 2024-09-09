#pragma once
#include <SFML/Graphics.hpp>
#include "Colicionable.h"

#pragma once
#include <SFML/Graphics.hpp>
#include "Colicionable.h"

class Bala : public sf::Drawable, public Colicionable {
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _velocidad;

public:
   bool murio;
    Bala(const sf::Vector2f& position, float rotation);
    void update();
    sf::FloatRect getBounds() const override;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

