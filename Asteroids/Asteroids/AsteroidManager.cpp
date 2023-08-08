#include "AsteroidManager.h"
#include "SoundManager.h"

AsteroidManager* AsteroidManager::s_instance = nullptr;

AsteroidManager::AsteroidManager()
{
	ba_tex.loadFromFile("../graphics/BigAsteroid.png");
	ma_tex.loadFromFile("../graphics/MediumAsteroid.png");
	sa_tex.loadFromFile("../graphics/SmallAsteroid.png");
}

AsteroidManager::~AsteroidManager()
{
	delete s_instance;
}

void AsteroidManager::add(int sw, int sh)
{
	for(int i = 0; i < ASTEROIDS_COUNT; i++)
		bigAsteroids.push_back(Asteroid(sw, sh, ba_tex));
}

void AsteroidManager::add(float startX, float startY, asteroidType type)
{
	if(type == MEDIUM)
		mediumAsteroids.push_back(Asteroid(startX, startY, ma_tex, type));
	else
		smallAsteroids.push_back(Asteroid(startX, startY, sa_tex, type));
}

bool AsteroidManager::checkCollisionShip(std::vector<Asteroid>& asteroids, sf::FloatRect& position)
{
	for (Asteroid& a : asteroids)
	{
		if (a.getPosition().intersects(position))
		{
			return true;
		}
	}

	return false;
}

bool AsteroidManager::collisionShip(sf::FloatRect position)
{
	return (checkCollisionShip(bigAsteroids, position) || 
		checkCollisionShip(mediumAsteroids, position) || 
		checkCollisionShip(smallAsteroids, position));
}

void AsteroidManager::checkCollisionBullet(std::vector<Asteroid>& asteroids, std::vector<Bullet>& bullets)
{
	for (auto it_a = asteroids.begin(); it_a != asteroids.end();)
	{
		bool b_hit = false;

		for (auto it_b = bullets.begin(); it_b != bullets.end();)
		{
			if (it_a->getPosition().intersects(it_b->getPosition()))
			{
				it_b = bullets.erase(it_b);
				b_hit = true;
				break;
			}
			else
				it_b++;
		}

		if (b_hit)
		{
			float x = it_a->getPosition().left + it_a->getPosition().width / 2;
			float y = it_a->getPosition().top + it_a->getPosition().height / 2;

			if (it_a->getType() == BIG)
			{
				add(x - 1, y - 1, MEDIUM);
				add(x + 1, y + 1, MEDIUM);
			}
			else if (it_a->getType() == MEDIUM)
			{
				add(x - 1, y - 1, SMALL);
				add(x + 1, y + 1, SMALL);
			}

			// Need to use Asteroid& operator= function in Asteroid.h becuase it_a points to another asteroid
			// while it is an asteroid just different
			// Need to copy values from other to this in that function oterwise it could destroy different asteroid
			it_a = asteroids.erase(it_a);
			TheSoundManager::Instance()->play(EXPLOSION);
		}
		else
			it_a++;
	}
}

void AsteroidManager::collisionBullet(std::vector<Bullet>& bullets)
{
	checkCollisionBullet(bigAsteroids, bullets);
	checkCollisionBullet(mediumAsteroids, bullets);
	checkCollisionBullet(smallAsteroids, bullets);
}

void AsteroidManager::clear()
{
	bigAsteroids.clear();
	mediumAsteroids.clear();
	smallAsteroids.clear();
}

int AsteroidManager::asteroidsCount()
{
	return (bigAsteroids.size() + mediumAsteroids.size() + smallAsteroids.size());
}

void AsteroidManager::draw(sf::RenderWindow& window)
{
	for (Asteroid& a : bigAsteroids) a.draw(window);
	for (Asteroid& a : mediumAsteroids) a.draw(window);
	for (Asteroid& a : smallAsteroids) a.draw(window);
}

void AsteroidManager::update(sf::Time dt, int sw, int sh)
{
	for (Asteroid& a : bigAsteroids) a.update(dt, sw, sh);
	for (Asteroid& a : mediumAsteroids) a.update(dt, sw, sh);
	for (Asteroid& a : smallAsteroids) a.update(dt, sw, sh);
}
