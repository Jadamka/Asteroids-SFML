#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "Asteroid.h"
#include "AsteroidManager.h"
#include "SoundManager.h"

#define WIDTH 800
#define HEIGHT 600

int main()
{
    bool restart = false;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Asteroids", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;
    
    sf::Font font;
    font.loadFromFile("../fonts/Death Star.otf");
    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(60);
    message.setFillColor(sf::Color::White);
    message.setString("PRESS 'R' TO RESTART");

    sf::FloatRect textCenter = message.getLocalBounds();
    message.setOrigin(textCenter.left + textCenter.width / 2, textCenter.top + textCenter.height / 2);
    message.setPosition(WIDTH / 2, HEIGHT / 2);

    sf::RectangleShape textBg;
    textBg.setOutlineColor(sf::Color::White);
    textBg.setOutlineThickness(5);
    textBg.setFillColor(sf::Color::Black);
    textBg.setSize(sf::Vector2f(WIDTH - 100, HEIGHT / 2));
    textBg.setOrigin(textBg.getLocalBounds().left + textBg.getLocalBounds().width / 2, textBg.getLocalBounds().top + textBg.getLocalBounds().height / 2);
    textBg.setPosition(message.getPosition());

    Ship ship(WIDTH / 2, HEIGHT / 2);
    TheAsteroidManager::Instance()->add(window.getSize().x, window.getSize().y);
    TheSoundManager::Instance()->createSounds();

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && restart)
        {
            TheAsteroidManager::Instance()->clear();
            TheAsteroidManager::Instance()->add(window.getSize().x, window.getSize().y);
            ship = Ship(window.getSize().x / 2, window.getSize().y / 2);
            restart = false;
        }

        if (TheAsteroidManager::Instance()->collisionShip(ship.getPosition()) && !ship.getDead())
        {
            ship.setDead();
            restart = true;
        }

        // Cant add this line above to if statement with ||, because audio of dead gets bugged and plays in a weird tone
        if (TheAsteroidManager::Instance()->asteroidsCount() <= 0)
            restart = true;

        TheAsteroidManager::Instance()->collisionBullet(ship.getBullets());

        sf::Time dt = clock.restart();

        ship.update(dt, window.getSize().x, window.getSize().y);
        TheAsteroidManager::Instance()->update(dt, window.getSize().x, window.getSize().y);

        window.clear();

        ship.draw(window);
        TheAsteroidManager::Instance()->draw(window);
        if (restart)
        {
            window.draw(textBg);
            window.draw(message);
        }

        window.display();
    }

    TheSoundManager::Instance()->dispose();

    return 0;
}