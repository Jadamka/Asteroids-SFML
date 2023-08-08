#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Bullet.h"

class Ship
{
private:
	sf::Texture t_tex;
	sf::Texture t_move_tex;
	sf::Sprite s_sprite;
	sf::Vector2f v_position;
	sf::Vector2f v_velocity;
	bool b_move = false;
	bool b_rotateLeft = false;
	bool b_rotateRight = false;
	float f_animation = 0.0000002f;
	float f_rotateSpeed;
	float f_angle;
	const float MAX_SPEED = 300.0f;
	const float ACCELERATION = 175.0f;
	const float FRICTION = 0.75f;
	std::vector<Bullet> bullets;
	float f_base_shot_timer = 0.15f;
	float f_shot_timer = 0.0f;
	bool b_dead;
public:
	Ship(float startX, float startY);
	sf::FloatRect getPosition();
	void move();
	void stopmMove();
	void rotateLeft();
	void stopRotateLeft();
	void rotateRight();
	void stopRotateRight();
	void setDead();
	std::vector<Bullet>& getBullets();
	void draw(sf::RenderWindow& window);
	void update(sf::Time dt, int sw, int sh);
};