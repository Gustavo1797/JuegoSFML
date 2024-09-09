#include "TanqueRapido.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

TanqueEnemigo::TanqueEnemigo(float startX, float startY) {
    _Velocidad = { 1, 1 };
    _texture.loadFromFile("TanqueRapido1.jpg");

    if (!_texture.loadFromFile("TanqueRapido1.jpg")) {
        //ESCRIBE EL ERROR
        std::cout << "Error al cargar la textura del enemigo" << std::endl;
    }
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
    _sprite.setPosition(startX, startY);
    _sprite.setRotation(180);

    murio = false;
    disparo = false;
    _saludBase = 100;
    _saludActual = 100;
}

void TanqueEnemigo::disparar() {
    Bala bala(_sprite.getPosition(), _sprite.getRotation());
    _balas.push_back(bala);
}

void TanqueEnemigo::updateBullets() {
    for (auto& bala : _balas) {
        bala.update();
    }
}

void TanqueEnemigo::restarVida(int cantidad) {
    _saludActual -= cantidad;
    if (_saludActual <= 0) {
        murio = true;
        _saludActual = 0;
    }
}

std::vector<Bala>& TanqueEnemigo::getBullet() {
    return _balas;
}

void TanqueEnemigo::update(std::vector<TanqueEnemigo*>& otrosTanques) {
    if (_relojMovimiento.getElapsedTime().asSeconds() > 0.5) {
        int direction = std::rand() % 4;
        switch (direction) {
        case 0:
            _Velocidad = { 0, -4 };
            _sprite.setRotation(0);
            break;
        case 1:
            _Velocidad = { -4, 0 };
            _sprite.setRotation(270);
            break;
        case 2:
            _Velocidad = { 0, 4 };
            _sprite.setRotation(180);
            break;
        case 3:
            _Velocidad = { 4, 0 };
            _sprite.setRotation(90);
            break;
        }
        _relojMovimiento.restart();
    }

    _sprite.move(_Velocidad);

    // LIMITES DEL TANQUE Y CAMBIA DE DIRECCION
    sf::Vector2f position = _sprite.getPosition();
    sf::FloatRect bounds = _sprite.getGlobalBounds();
    if (position.x - bounds.width / 2 < 0) {
        _sprite.setPosition(bounds.width / 2, position.y);
        _Velocidad = { 3, 0 };
        _sprite.setRotation(90);
    }
    else if (position.y - bounds.height / 2 < 0) {
        _sprite.setPosition(position.x, bounds.height / 2);
        _Velocidad = { 0, 3 };
        _sprite.setRotation(180);
    }
    else if (position.x + bounds.width / 2 > 1200) {
        _sprite.setPosition(1200 - bounds.width / 2, position.y);
        _Velocidad = { -3, 0 };
        _sprite.setRotation(270);
    }
    else if (position.y + bounds.height / 2 > 800) {
        _sprite.setPosition(position.x, 800 - bounds.height / 2);
        _Velocidad = { 0, -3 };
        _sprite.setRotation(0);
    }

    if (_relojDisparo.getElapsedTime().asSeconds() > 1.0f + static_cast<float>(std::rand() % 2000) / 1000.0f) {
        disparar();
        _relojDisparo.restart();
    }


    _balas.erase(std::remove_if(_balas.begin(), _balas.end(), [](const Bala& bala) {
        sf::FloatRect bounds = bala.getBounds();
        return bounds.left + bounds.width < 0 || bounds.top + bounds.height < 0 ||
            bounds.left > 1200 || bounds.top > 800;
        }), _balas.end());

 // Verificar colisiones con otros tanques
    for (auto& otroTanque : otrosTanques) {
        if (otroTanque != this && this->isCollision(*otroTanque)) {
            // Cambiar dirección al chocar
            int direction = std::rand() % 4;
            switch (direction) {
            case 0:
                _Velocidad = { 0, -4 };
                _sprite.setRotation(0);
                break;
            case 1:
                _Velocidad = { -4, 0 };
                _sprite.setRotation(270);
                break;
            case 2:
                _Velocidad = { 0, 4 };
                _sprite.setRotation(180);
                break;
            case 3:
                _Velocidad = { 4, 0 };
                _sprite.setRotation(90);
                break;
            }
            _sprite.move(_Velocidad); // Mover en dirección opuesta
            break; // Solo cambiar dirección una vez por colisión
        }

        for (auto& bala : _balas) {
        for (auto& otroTanque : otrosTanques) {
            if (otroTanque != this && bala.getBounds().intersects(otroTanque->getBounds())) {
                // Restar vida al tanque enemigo
                 // Ajusta la cantidad de daño según sea necesario
                bala.murio = true; // Marca la bala para eliminación
            }
        }}

        _balas.erase(std::remove_if(_balas.begin(), _balas.end(), [](const Bala& bala) {
        return bala.murio;
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
    }
}


    updateBullets();

}///CIERRE UPDATE

void TanqueEnemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
    for (const auto& bala : _balas) {
        target.draw(bala, states);
    }
}

sf::FloatRect TanqueEnemigo::getBounds() const {
    return _sprite.getGlobalBounds();
}
