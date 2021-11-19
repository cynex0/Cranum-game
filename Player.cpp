#include "Player.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <string>

Player::Player(double x_, double y_)
	:walk_animation("sprites/player/walk", 13),
	idle_animation("sprites/player/idle", 11)
{
	x = x_;
	y = y_;
	dx = 0;
	dy = 0;

	lives = 3;
	state = 0;

	current_frame = 0;
	dir = 'r';

	//for (int i = 0; i < 11; i++) {
		//idle_animation[i].loadFromFile("sprites/player/idle/frame" + std::to_string(i) + ".png");
	//}

	for (int i = 0; i < 18; i++) {
		attack_animation[i].loadFromFile("sprites/player/attack/frame" + std::to_string(i) + ".png");
	}

	for (int i = 0; i < 15; i++) {
		dead_animation[i].loadFromFile("sprites/player/dead/frame" + std::to_string(i) + ".png");
	}

	for (int i = 0; i < 8; i++) {
		hit_animation[i].loadFromFile("sprites/player/hit/frame" + std::to_string(i) + ".png");
	}

	
	//for (int i = 0; i < 13; i++) {
		//walk_animation[i].loadFromFile("sprites/player/walk/frame" + std::to_string(i) + ".png");
	//}

}

Player::~Player() {}

void Player::update(int dt_) {
	x += dx * dt_;
	y += dy * dt_;

	anim_time += dt_;
	current_frame = (anim_time / TICKRATE) % 11;

	if ((dx == 0) && (dy == 0))
		anim = idle;

	if (dx > 0) {
		anim = walk;
		dir = 'r';
	}
	else if (dx < 0) {
		anim = walk;
		dir = 'l';
	}
	
	switch (anim) {
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
