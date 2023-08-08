#include "Bullet.h"

Bullet::Bullet(float startX, float startY, float f_angle)
{
	f_alive_timer = 0.6f;

	acc = { 0, 0 };

	v_position.x = startX;
	v_position.y = startY;

	s_shape.setSize(sf::Vector2f(5, 5));
	s_shape.setOrigin(s_shape.getLocalBounds().left + s_shape.getLocalBounds().width / 2,
		s_shape.getLocalBounds().top + s_shape.getLocalBounds().height / 2);
	s_shape.setPosition(v_position);
}

sf::FloatRect Bullet::getPosition()
{
	return s_shape.getGlobalBounds();
}

float Bullet::getAliveTimer()
{
	return f_alive_timer;
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(s_shape);
}

void Bullet::update(sf::Time dt, int sw, int sh, float f_angle)
{
	if (b_shot)
	{
		acc = sf::Vector2f(sin(f_angle * DEG_TO_RAD), -cos(f_angle * DEG_TO_RAD));
		b_shot = false;
	}

	v_position.x += acc.x * f_speed * dt.asSeconds();
	v_position.y += acc.y * f_speed * dt.asSeconds();

	if (v_position.x < 0) v_position.x = sw;
	if (v_position.x > sw) v_position.x = 0;
	if (v_position.y < 0) v_position.y = sh;
	if (v_position.y > sh) v_position.y = 0;

	s_shape.setPosition(v_position);

	f_alive_timer -= dt.asSeconds();
}