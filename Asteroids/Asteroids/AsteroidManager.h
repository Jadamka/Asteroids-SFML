#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Asteroid.h"
#include "Bullet.h"

#define ASTEROIDS_COUNT 4

class AsteroidManager
{
private:
	static AsteroidManager* s_instance;
	AsteroidManager();
	~AsteroidManager();
	std::vector<Asteroid> bigAsteroids;
	std::vector<Asteroid> mediumAsteroids;
	std::vector<Asteroid> smallAsteroids;
	sf::Texture ba_tex;
	sf::Texture ma_tex;
	sf::Texture sa_tex;
	bool checkCollisionShip(std::vector<Asteroid>& asteroids, sf::FloatRect& position);
	void checkCollisionBullet(std::vector<Asteroid>& asteroids, std::vector<Bullet>& bullets);
public:
	static AsteroidManager* Instance()
	{
		if (s_instance == nullptr)
			s_instance = new AsteroidManager;

		return s_instance;
	}
	void add(int sw, int sh);
	void add(float startX, float startY, asteroidType type);
	bool collisionShip(sf::FloatRect position);
	void collisionBullet(std::vector<Bullet>& bullets);
	void clear();
	int asteroidsCount();
	void draw(sf::RenderWindow& window);
	void update(sf::Time dt, int sw, int sh);
};

typedef AsteroidManager TheAsteroidManager;