#pragma once

#include <SFML/Graphics.hpp>

enum asteroidType
{
	BIG,
	MEDIUM,
	SMALL
};

class Asteroid
{
private:
	sf::Vector2f v_position;
	sf::Sprite s_sprite;
	sf::CircleShape hitbox;
	const float f_BAsteroidSpeed = 50.0f;
	const float f_MAsteroidSpeed = 75.0f;
	const float f_SAsteroidSpeed = 150.5f;
	const float f_Bscale = 7.5f;
	const float f_Mscale = 4.5f;
	const float f_Sscale = 2.5f;
	float f_speed;
	float f_dx;
	float f_dy;
	asteroidType e_type;
	void createHitbox();
public:
	Asteroid(int sw, int sh, sf::Texture& t_tex);
	Asteroid(float startX, float startY, sf::Texture& t_tex, asteroidType type);
	sf::FloatRect getPosition();
	asteroidType getType();
	void draw(sf::RenderWindow& window);
	void update(sf::Time dt, int sw, int sh);
	Asteroid& operator=(const Asteroid& other)
	{
		if (this != &other)
		{
			this->v_position = other.v_position;
			this->f_dx = other.f_dx;
			this->f_dy = other.f_dy;
		}

		return *this;
	}
};