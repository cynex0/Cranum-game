#include "Player.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <string>

Player::Player(double x_, double y_):
	walk_animation("sprites/player/walk", 13),
	idle_animation("sprites/player/idle", 11),
	attack_animation("sprites/player/attack", 18),
	death_animation("sprites/player/death", 15),
	hit_animation("sprites/player/hit", 8)
{
	x = x_;
	y = y_;
	dx = 0;
	dy = 0;

	lives = 3;
	state = idle;

	current_frame = 0;
	anim_time = 0;
	dir = 'r';
}

Player::~Player() {}

void Player::update(int dt_) {
	x += dx * dt_;
	y += dy * dt_;

	anim_time += dt_;
	//TODO: calculate for different animation lengths
	current_frame = (anim_time / TICKRATE) % 11;

	if ((dx == 0) && (dy == 0))
		state = idle;

	if (dx > 0) {
		state = walk;
		dir = 'r';
	}
	else if (dx < 0) {
		state = walk;
		dir = 'l';
	}
	
	switch (state) {
		case idle: 
			sprite.setTexture(idle_animation.frames[dir].at(current_frame));
			break;
		case walk:  
			sprite.setTexture(walk_animation.frames[dir].at(current_frame));
			break;
	}
	
	sprite.setPosition(x, y);
	dx = 0;
}

void Player::draw(sf::RenderWindow window) {
	window.draw(sprite);
}

void Player::setdX(double dx_) {
	dx = dx_;
}

void Player::setdY(double dy_) {
	dy = dy_;
}
