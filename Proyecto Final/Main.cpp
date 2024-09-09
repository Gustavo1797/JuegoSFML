#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "TanquePlayer1.h"
#include "TanqueRapido.h"
#include "rlutil.h"
#include "FuncionesMenu.h"
#include "Bala.h"

int main()
{
    // GENERADOR DE NUMEROS ALEATORIOS.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Crear la ventana del juego
    sf::RenderWindow window(sf::VideoMode(800, 600), "Gotham City.");
    window.setFramerateLimit(60);

    // Crear el objeto del jugador
    TanquePlayer1 Player;

    // Crear un vector de enemigos
    std::vector<TanqueEnemigo*> enemigos;
    int numeroEnemigos = 0;
    sf::Clock relojEnemigos;
    const float tiempoEntreApariciones = 10.0f; //EL TIEMPO DE APARICION SE CONTROLA ACA

    // CREAR LOS 2 PRIMEROS ENEMIGOS EN EXTREMOS
    enemigos.push_back(new TanqueEnemigo (50, 50));  // Posición extrema izquierda
    enemigos.push_back(new TanqueEnemigo (750, 50)); // Posición extrema derecha
    numeroEnemigos = 2;

    // LOOP
    while (window.isOpen())
    {
        // Manejar eventos de la ventana
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ES TIEMPO DE AGREGAR LOS ENEMIGOS? NO MAS DE 6 ENEMIGOS.
        if (relojEnemigos.getElapsedTime().asSeconds() > tiempoEntreApariciones && numeroEnemigos < 6) {
            // AÑADE 2 NUEVO ENEMIGOS
            for (int i = 0; i < 1; ++i) {
                float x = static_cast<float>(std::rand() % (window.getSize().x - 50) + 25);
                float y = static_cast<float>(std::rand() % (window.getSize().y / 2)); // Solo en la mitad superior
                try {
               enemigos.push_back(new TanqueEnemigo (x, y));
                  numeroEnemigos++;
                }
                catch (const std::exception& e) {
                    std::cout << "Error al crear enemigo: " << e.what() << std::endl;
                }
            }
            relojEnemigos.restart();
        }



        // Actualizar los objetos del juego
         Player.update(enemigos); // Actualiza jugador
    for (auto& enemigo : enemigos) {
        enemigo->update(enemigos); // Actualiza cada tanque enemigo
    }
        // Dibujar todo en la ventana
        window.clear();
        window.draw(Player);
        for (const auto enemigo : enemigos) {
            window.draw(*enemigo);
        }
        window.display();
    }

    return 0;
}
