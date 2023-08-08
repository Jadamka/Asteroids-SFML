#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"

class Bullet
{
private:
	sf::Vector2f v_position;
	sf::RectangleShape s_shape;
	sf::Vector2f acc;
	float f_alive_timer;
	float f_speed = 700.0f;
	bool b_shot = true;
public:
	Bullet(float startX, float startY, float f_angle);
	sf::FloatRect getPosition();
	float getAliveTimer();
	void draw(sf::RenderWindow& window);
	void update(sf::Time dt, int sw, int sh, float f_angle);
};