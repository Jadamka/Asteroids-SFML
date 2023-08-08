#include "Asteroid.h"
#include <random>
#include <iostream>

Asteroid::Asteroid(int sw, int sh, sf::Texture& t_tex)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> velocity(-1.0, 1.0);
	std::uniform_int_distribution<int> spawnX(0, sw);
	std::uniform_int_distribution<int> spawnY(0, sh);
	std::uniform_int_distribution<int> betweenTwo(1, 2);

	f_dx = velocity(gen);
	f_dy = velocity(gen);

	if (f_dx == 0 && f_dy == 0)
	{
		f_dx = 1;
		f_dy = 1;
	}

	f_speed = f_BAsteroidSpeed;

	v_position.x = (float)spawnX(gen);
	v_position.y = (float)spawnY(gen);

	if (v_position.x > sw / 2 - 100 && v_position.x < sw / 2 + 100 &&
		v_position.y > sh / 2 - 150 && v_position.y < sh / 2 + 150)
	{
		float x = betweenTwo(gen);
		float y = betweenTwo(gen);
		if (x == 1)
			v_position.x = 100;
		else
			v_position.x = sw - 100;
		if (y == 1)
			v_position.y = 100;
		else
			v_position.y = sh - 100;
	}

	s_sprite.setTexture(t_tex);

	s_sprite.setOrigin(s_sprite.getLocalBounds().left + s_sprite.getLocalBounds().width / 2,
		s_sprite.getLocalBounds().top + s_sprite.getLocalBounds().height / 2);
	s_sprite.setScale(sf::Vector2f(f_Bscale, f_Bscale));

	s_sprite.setPosition(v_position);

	this->e_type = BIG;

	createHitbox();
}

Asteroid::Asteroid(float startX, float startY, sf::Texture& t_tex, asteroidType type)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> velocity(-1.0, 1.0);

	f_dx = velocity(gen);
	f_dy = velocity(gen);

	if (f_dx == 0 && f_dy == 0)
	{
		f_dx = 1;
		f_dy = 1;
	}

	v_position.x = startX;
	v_position.y = startY;

	s_sprite.setTexture(t_tex);

	if (type == asteroidType::MEDIUM)
	{
		f_speed = f_MAsteroidSpeed;
		s_sprite.setScale(sf::Vector2f(f_Mscale, f_Mscale));
	}
	else
	{
		f_speed = f_SAsteroidSpeed;
		s_sprite.setScale(sf::Vector2f(f_Sscale, f_Sscale));
	}

	s_sprite.setOrigin(s_sprite.getLocalBounds().left + s_sprite.getLocalBounds().width / 2,
		s_sprite.getLocalBounds().top + s_sprite.getLocalBounds().height / 2);

	s_sprite.setPosition(v_position);

	this->e_type = type;

	createHitbox();
}

void Asteroid::createHitbox()
{
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Green);
	hitbox.setOutlineThickness(3);
	hitbox.setOrigin(s_sprite.getOrigin());

	if (e_type == BIG)
		hitbox.setRadius(75);
	else if (e_type == MEDIUM)
		hitbox.setRadius(50);
	else
		hitbox.setRadius(25);

	/*if(e_type == BIG)
		hitbox.setSize(sf::Vector2f(s_sprite.getLocalBounds().width * 6, s_sprite.getLocalBounds().height * 6));
	else if(e_type == MEDIUM)
		hitbox.setSize(sf::Vector2f(s_sprite.getLocalBounds().width * 3.7, s_sprite.getLocalBounds().height * 3.7));
	else
		hitbox.setSize(sf::Vector2f(s_sprite.getLocalBounds().width * 2, s_sprite.getLocalBounds().height * 2));*/
}

sf::FloatRect Asteroid::getPosition()
{
	return hitbox.getGlobalBounds();
}

void Asteroid::draw(sf::RenderWindow& window)
{
	window.draw(s_sprite);
	//window.draw(hitbox);
}

asteroidType Asteroid::getType()
{
	return e_type;
}

void Asteroid::update(sf::Time dt, int sw, int sh)
{
	v_position.x += f_dx * f_speed * dt.asSeconds();
	v_position.y += f_dy * f_speed * dt.asSeconds();

	if (v_position.x < -s_sprite.getLocalBounds().width) v_position.x = sw + s_sprite.getLocalBounds().width;
	if (v_position.x > sw + s_sprite.getLocalBounds().width) v_position.x = -s_sprite.getLocalBounds().width;
	if (v_position.y < -s_sprite.getLocalBounds().height) v_position.y = sh + s_sprite.getLocalBounds().height;
	if (v_position.y > sh + s_sprite.getLocalBounds().height) v_position.y = -s_sprite.getLocalBounds().height;

	s_sprite.setPosition(v_position);
	if(e_type == BIG)
		hitbox.setPosition(v_position.x - s_sprite.getLocalBounds().width * 2.5, v_position.y - s_sprite.getLocalBounds().height * 2.5);
	else if(e_type == MEDIUM)
		hitbox.setPosition(v_position.x - s_sprite.getLocalBounds().width - 10, v_position.y - s_sprite.getLocalBounds().height - 10);
	else
		hitbox.setPosition(v_position.x - s_sprite.getLocalBounds().width / 2, v_position.y - s_sprite.getLocalBounds().height / 2);
}