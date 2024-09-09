
#pragma once
#include <SFML/Graphics.hpp>
#include "Colicionable.h"
#include "Bala.h"
#include <vector>
#include "TanqueRapido.h"

class TanquePlayer1 : public sf::Drawable, public Colicionable {
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _Velocidad;
    std::vector<Bala> _balas;
    sf::Clock _relojDisparo;
    int vida;
    int _saludBase;
    int _saludActual;
    int _puntos;
    bool murio;
    bool disparo;


public:
    TanquePlayer1();
    void update();

    void update(const std::vector<TanqueEnemigo*>& enemigos);
    bool checkCollision(const sf::Sprite& other) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
    void disparar();
    bool getMurio();
    void setMurio(bool);
    void setSalud(int);
    void setDisparo(bool);
    bool getDisparo() const;
    void setVelocidad();

    int getSalud();
    void drawBala(sf::RenderWindow&);
    void updateBullets();
    void restarVida(int);
    int getSaludActual();
    int getSaludBase();
    int getPuntos();
    TanquePlayer1* getPtr();
    std::vector<Bala>& getBullet();
};
