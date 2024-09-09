#pragma once
#include <SFML\Graphics.hpp>

class Colicionable
{
public:
    virtual sf::FloatRect getBounds() const = 0;

    bool isCollision(Colicionable& obj) const;
};