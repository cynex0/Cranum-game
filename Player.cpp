#include "Player.h"
#include "IMoveable.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

Player::Player(double x_, double y_)
	:
	attack_cd(100),
	transform_cd(250)
{
	x = x_;
	y = y_;
	dx = 0;
	dy = 0;

	lives = 3;
	state = State::idle;
	isHead = false;

	animations.add(State::idle, "sprites/player/idle", 11);
	animations.add(State::walk, "sprites/player/walk", 13);
	animations.add(State::attacking, "sprites/player/attack", 18);
	animations.add(State::death, "sprites/player/death", 15);
	animations.add(State::take_dmg, "sprites/player/hit", 8);
	animations.add(State::transforming, "sprites/player/transform", 10);
	animations.add(State::transforming_back, "sprites/player/transform", -10);
	animations.add(State::rolling, "sprites/player/roll", 10);

	last_attack = 0;
	last_transform = 0;
	dir = 'r';
}

Player::~Player() {}

void Player::update(int dt_) {
	if ((state != State::attacking) && (state != State::transforming) && (state != State::transforming_back)) {
		if ((dx == 0) && (dy == 0)) {
			if (!isHead)
				state = State::idle;
			else
				state = State::rolling;
		}
		else if (dx > 0) {
			if (!isHead)
				state = State::walk;
			else
				state = State::rolling;
			dir = 'r';
		}
		else if (dx < 0) {
			if (!isHead)
				state = State::walk;
			else
				state = State::rolling;
			dir = 'l';
		}
	}

	// reset one-time animations
	if ((state == State::attacking) && (animations.animations[state].hasEnded())) {
		animations.animations[state].reset();
		state = State::idle;
	}
	if (((state == State::transforming) || (state == State::transforming_back)) && (animations.animations[state].hasEnded())) {
		animations.animations[state].reset();
		state = State::idle;
	}

	//TODO: fix animation position
	//TODO: make head stay in place when not moving
	// update animations
	
	animations.animations[state].update(dt_);
	animations.animations[state].applyToSprite(sprite, dir);
	//update position
	if (state == State::walk || state == State::rolling) {
		x += dx * dt_;
		y += dy * dt_;
	}
	sprite.setPosition(x, y);

	dx = 0; //reset velocity for next loop
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Player::setdX(double dx_) {
	dx = dx_;
}

void Player::setdY(double dy_) {
	dy = dy_;
}

void Player::attack(double tp_) {
	if ((state == State::attacking) || (state == State::rolling) || (state == State::transforming) || (state == State::transforming_back))
		return;

	if (tp_ >= (last_attack + attack_cd)) {
		state = State::attacking;
		last_attack = tp_;
	}
}

void Player::transform(double tp_) {
	if ((state == State::attacking) || (state == State::transforming) || (state == State::transforming_back))
		return;

	if (tp_ >= (last_transform + transform_cd)) {
		if (!isHead) {
			state = State::transforming;
				isHead = true;
		}
		else {
			state = State::transforming_back;
				isHead = false;
		}
	}
}
