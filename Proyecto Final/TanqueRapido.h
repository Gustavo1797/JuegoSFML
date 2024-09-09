#pragma once
#include <SFML/Graphics.hpp>
#include "Bala.h"
#include "Colicionable.h"
#include <vector>


class TanqueEnemigo : public sf::Drawable, public Colicionable {
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _Velocidad;
    std::vector<Bala> _balas;
    sf::Clock _relojDisparo;
    sf::Clock _relojMovimiento;
    int vida;
    int _saludBase;
    int _saludActual;
    int _puntos;
    bool murio;
    bool disparo;

public:
    TanqueEnemigo(float startX, float startY);
    void update(std::vector<TanqueEnemigo*>& otrosTanques); // Declaración ajustada
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void disparar();
    void updateBullets();
    void restarVida(int cantidad);
    std::vector<Bala>& getBullet();
    void setVelocidad();
};
