#include "Player.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <string>

Player::Player(double x_, double y_){
	x = x_;
	y = y_;
	dx = 0;
	dy = 0;

	lives = 3;
	state = idle;

	animations.add(idle, "sprites/player/idle", 11);
	animations.add(walk, "sprites/player/walk", 13);
	animations.add(attacking, "sprites/player/attack", 18);
	animations.add(death, "sprites/player/death", 15);
	animations.add(take_dmg, "sprites/player/hit", 8);

	current_frame = 0;
	current_animation = animations.get(state);
	anim_time = 0;
	last_attack = 0;
	dir = 'r';
}

Player::~Player() {}

void Player::update(int dt_) {
	//TODO: fix animations not playing from beginning
	anim_time += dt_;
	
	if (state != attacking) {
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
	}
	else {
		dx = 0;
		dy = 0;
	}
	
	current_animation = animations.get(state);
	current_frame = (anim_time / TICKRATE) % current_animation.getLength();

	if (state == attacking) {
		if (current_frame >= current_animation.getLength() - 1) {
			state = idle;
			last_attack = anim_time;
		}
	}

	//TODO: private data + getters
	//TODO: fix animation position
	sprite.setTexture(current_animation.frames[dir].at(current_frame));
	
	x += dx * dt_;
	y += dy * dt_;
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

void Player::attack() {
	if ((anim_time - last_attack >= 500) && (state != attacking)) {
		state = attacking;
	}
}
