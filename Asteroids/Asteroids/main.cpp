#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "Asteroid.h"
#include "AsteroidManager.h"

#define WIDTH 800
#define HEIGHT 600

#define ASTEROIDS_COUNT 4

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Asteroids", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;

    Ship ship(WIDTH / 2, HEIGHT / 2);

    for(int i = 0; i < ASTEROIDS_COUNT; i++)
        TheAsteroidManager::Instance()->add(window.getSize().x, window.getSize().y);

    sf::Clock clock;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ship.rotateLeft();
        else
            ship.stopRotateLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ship.rotateRight();
        else
            ship.stopRotateRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ship.move();
        else
            ship.stopmMove();

        if (TheAsteroidManager::Instance()->collisionShip(ship.getPosition()))
            ship.setDead();
        TheAsteroidManager::Instance()->collisionBullet(ship.getBullets());

        sf::Time dt = clock.restart();

        ship.update(dt, window.getSize().x, window.getSize().y);
        TheAsteroidManager::Instance()->update(dt, window.getSize().x, window.getSize().y);

        window.clear();

        ship.draw(window);
        TheAsteroidManager::Instance()->draw(window);

        window.display();
    }

    return 0;
}