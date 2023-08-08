#include "Ship.h"

Ship::Ship(float startX, float startY)
{
	f_rotateSpeed = 50.0f;
	f_angle = 0.0f;

	v_velocity = { 0, 0 };

	v_position.x = startX;
	v_position.y = startY;

	t_tex.loadFromFile("../graphics/ship.png");
	t_move_tex.loadFromFile("../graphics/ship_move.png");

	s_sprite.setTexture(t_tex);

	s_sprite.setOrigin(s_sprite.getLocalBounds().left + s_sprite.getLocalBounds().width / 2, 
		s_sprite.getLocalBounds().top + s_sprite.getLocalBounds().height / 2);
	s_sprite.setScale(sf::Vector2f(1.2, 1.2));

	s_sprite.setRotation(f_angle);

	s_sprite.setPosition(v_position);

	b_dead = false;
}

sf::FloatRect Ship::getPosition()
{
	return s_sprite.getGlobalBounds();
}

void Ship::move()
{
	b_move = true;
}

void Ship::stopmMove()
{
	b_move = false;
}

void Ship::rotateLeft()
{
	b_rotateLeft = true;
}

void Ship::stopRotateLeft()
{
	b_rotateLeft = false;
}

void Ship::rotateRight()
{
	b_rotateRight = true;
}

void Ship::stopRotateRight()
{
	b_rotateRight = false;
}

void Ship::setDead()
{
	b_dead = true;
}

std::vector<Bullet>& Ship::getBullets()
{
	return bullets;
}

void Ship::draw(sf::RenderWindow& window)
{
	if (!b_dead)
	{
		window.draw(s_sprite);

		for (Bullet b : bullets)
			b.draw(window);
	}
}

void Ship::update(sf::Time dt, int sw, int sh)
{
	if (!b_dead)
	{
		for (Bullet& b : bullets)
			b.update(dt, sw, sh, f_angle);

		if (b_rotateLeft)
		{
			f_angle -= 5.0f * f_rotateSpeed * dt.asSeconds();

			s_sprite.setRotation(f_angle);
		}
		if (b_rotateRight)
		{
			f_angle += 5.0f * f_rotateSpeed * dt.asSeconds();

			s_sprite.setRotation(f_angle);
		}

		sf::Clock animationSwitchClock;

		if (b_move)
		{
			sf::Vector2f accVec = sf::Vector2f(sin(f_angle * DEG_TO_RAD), -cos(f_angle * DEG_TO_RAD)) * ACCELERATION;

			v_velocity += accVec * dt.asSeconds();

			float speed = sqrt(v_velocity.x * v_velocity.x + v_velocity.y * v_velocity.y);
			if (speed > MAX_SPEED)
				v_velocity *= MAX_SPEED / speed;

			v_position += v_velocity * dt.asSeconds();
			s_sprite.setPosition(v_position);

			if (animationSwitchClock.getElapsedTime().asSeconds() > f_animation)
			{
				animationSwitchClock.restart();

				if (s_sprite.getTexture() == &t_tex)
					s_sprite.setTexture(t_move_tex);
				else
					s_sprite.setTexture(t_tex);
			}
		}
		else
		{
			s_sprite.setTexture(t_tex);
			v_velocity *= (1.0f - FRICTION * dt.asSeconds());

			v_position += v_velocity * dt.asSeconds();
			s_sprite.setPosition(v_position);

			if (abs(v_velocity.x) < 0.1f && abs(v_velocity.y) < 0.1f)
				v_velocity = { 0, 0 };
		}

		if (v_position.x < -s_sprite.getLocalBounds().width)
			v_position.x = sw + s_sprite.getLocalBounds().width;
		if (v_position.x > sw + s_sprite.getLocalBounds().width)
			v_position.x = -s_sprite.getLocalBounds().width;
		if (v_position.y < -s_sprite.getLocalBounds().height)
			v_position.y = sh + s_sprite.getLocalBounds().height;
		if (v_position.y > sh + s_sprite.getLocalBounds().height)
			v_position.y = s_sprite.getLocalBounds().height;

		s_sprite.setPosition(v_position);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && f_shot_timer <= 0.0f)
		{
			bullets.push_back(Bullet(v_position.x, v_position.y, 0));
			f_shot_timer = f_base_shot_timer;
		}

		if (f_shot_timer > 0.0f)
			f_shot_timer -= dt.asSeconds();

		for (auto it = bullets.begin(); it != bullets.end();)
		{
			if (it->getAliveTimer() <= 0.0f)
			{
				it = bullets.erase(it);
			}
			else
				it++;
		}
	}
}