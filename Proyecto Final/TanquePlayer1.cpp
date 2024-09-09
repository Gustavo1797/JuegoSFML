#include "TanquePlayer1.h"
#include "TanqueRapido.h"
#include <algorithm>

TanquePlayer1::TanquePlayer1() {
    _Velocidad = { 0.25, 0.25 };
    _texture.loadFromFile("Tanque1.jpg");
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
    _sprite.setPosition(200, 700);

    murio = false;
    disparo = false;
    _saludBase = 100;
    _saludActual = 100;
}

bool TanquePlayer1::getMurio() {
    return murio;
}

void TanquePlayer1::setMurio(bool estado) {
    murio = estado;
}


void TanquePlayer1::setSalud(int salud) {
    _saludActual = salud;
}

bool TanquePlayer1::getDisparo() const {
    return disparo;
}

int TanquePlayer1::getSalud() {
    return _saludActual;
}

void TanquePlayer1::drawBala(sf::RenderWindow& window) {
    for (auto& bala : _balas) {
        window.draw(bala);
    }
}

void TanquePlayer1::updateBullets() {
    for (auto& bala : _balas) {
        bala.update();
    }
}

void TanquePlayer1::restarVida(int cantidad) {
    _saludActual -= cantidad;
    if (_saludActual <= 0) {
        murio = true;
        _saludActual = 0;
    }
}

int TanquePlayer1::getSaludActual() {
    return _saludActual;
}

int TanquePlayer1::getSaludBase() {
    return _saludBase;
}

int TanquePlayer1::getPuntos() {
    return _puntos;
}

TanquePlayer1* TanquePlayer1::getPtr() {
    return this;
}

std::vector<Bala>& TanquePlayer1::getBullet() {
    return _balas;
}

void TanquePlayer1::disparar() {
    Bala bala(_sprite.getPosition(), _sprite.getRotation());
    _balas.push_back(bala);
}



void TanquePlayer1::update(const std::vector<TanqueEnemigo*>& enemigos) {
    _Velocidad = { 0, 0 };

    // Guarda la posición actual antes de mover el tanque
    sf::Vector2f posicionAnterior = _sprite.getPosition();


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _Velocidad.y = -4;
        _sprite.setRotation(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _Velocidad.x = -4;
        _sprite.setRotation(270);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _Velocidad.y = 4;
        _sprite.setRotation(180);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _Velocidad.x = 4;
        _sprite.setRotation(90);
    }

    _sprite.move(_Velocidad);

    // Detección de colisiones con enemigos
    for (const auto& enemigo : enemigos) {
        if (_sprite.getGlobalBounds().intersects(enemigo->getBounds())) {
            _sprite.setPosition(posicionAnterior); // Volver a la posición anterior
            break;
        }
    }

    // CONTROLA FRECUENCIA DISPARO
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (_relojDisparo.getElapsedTime().asSeconds() >= 0.3f) {
            disparar();
            _relojDisparo.restart();
        }
    }

    // ACTUALIZA BALAS
    updateBullets();

    // ELIMINA LAS BALAS FUERA DE LA PANTALLA
    _balas.erase(std::remove_if(_balas.begin(), _balas.end(), [](const Bala& bala) {
        sf::FloatRect bounds = bala.getBounds();
        return bounds.left + bounds.width < 0 || bounds.top + bounds.height < 0 ||
            bounds.left > 800 || bounds.top > 600;
        }), _balas.end());

    // ACA CONTROLAMOS LIMITES DE TANQUES
    if (_sprite.getPosition().x - _sprite.getGlobalBounds().width / 2 < 0) {
        _sprite.setPosition(_sprite.getGlobalBounds().width / 2, _sprite.getPosition().y);
    }
    if (_sprite.getPosition().y - _sprite.getGlobalBounds().height / 2 < 0) {
        _sprite.setPosition(_sprite.getPosition().x, _sprite.getGlobalBounds().height / 2);
    }
    if (_sprite.getPosition().x + _sprite.getGlobalBounds().width / 2 > 800) {
        _sprite.setPosition(800 - _sprite.getGlobalBounds().width / 2, _sprite.getPosition().y);
    }
    if (_sprite.getPosition().y + _sprite.getGlobalBounds().height / 2 > 600) {
        _sprite.setPosition(_sprite.getPosition().x, 600 - _sprite.getGlobalBounds().height / 2);
    }}

     // DETECTAR COLISIONES CON ENEMIGOS Y REVERSAR MOVIMIENTO SI HAY COLISIÓN


void TanquePlayer1::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
    for (const auto& bala : _balas) {
        target.draw(bala, states);
    }
}


sf::FloatRect TanquePlayer1::getBounds() const {
    return _sprite.getGlobalBounds();
}
