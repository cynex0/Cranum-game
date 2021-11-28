#include "Player.h"
#include "Level.h"
#include "IMoveable.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

Player::Player(double x_, double y_):
	attack_cd(0.35),
	transform_cd(0.75)
{
	x = x_;
	y = y_;
	init_x = x;
	init_y = y;
	dx = 0;
	dy = 0;

	buffer.loadFromFile("sprites/death.wav");
	death_sound.setBuffer(buffer);
	death_sound.setLoop(false);
	death_sound.setVolume(50);

	//sprite.setScale(1.5, 1.5);

	state = State::idle;
	isHead = false;
	isOnGround = false;

	animations.add(State::idle, "sprites/player/idle", 11);
	animations.add(State::walk, "sprites/player/walk", 13);
	animations.add(State::attacking, "sprites/player/attack", 18);
	animations.add(State::death, "sprites/player/death", 15);
	animations.add(State::take_dmg, "sprites/player/hit", 8);
	animations.add(State::transforming, "sprites/player/transform", 10);
	animations.add(State::transforming_back, "sprites/player/transform", -10);
	animations.add(State::rolling, "sprites/player/roll", 10);

	last_attack = -attack_cd;
	last_transform = -transform_cd;
	dir = 'r';
}

Player::~Player() {}

void Player::reset() {
	state = State::idle;
	isHead = false;
	isOnGround = false;
	
	x = init_x;
	y = init_y;
	dx = 0;
	dy = 0;
}

void Player::update(float dt_, Level& level, sf::RenderWindow& window) {
	// Y:
	if (y < 0) {
		y = 0;
		dy = 0;
	}

	if (dy >= 0)
		isJumping = false;

	// X:
	if (x < 0) 
		x = 0;
	if (x + PLAYER_W > WINDOW_W)
		level.isCompleted = true;

	if ((state != State::attacking) && (state != State::transforming) && (state != State::transforming_back) && (state != State::death)) {
		if ((dx == 0)/* && (dy == 0)*/) {
			if (!isHead)
				state = State::idle;
		}
		else if (dx > 0) {
			if (!isHead)
				state = State::walk;		
			dir = 'r';
		}
		else if (dx < 0) {
			if (!isHead)
				state = State::walk;
			dir = 'l';
		}
		if (isHead)
			state = State::rolling;
	}
	else if (state == State::death) {
		dx = 0;
		dy = 0;
	}
	if (state == State::rolling && dx == 0) {
		if (dir == 'r')
			dx = PLAYER_DX;
		else
			dx = -PLAYER_DX;
	}

	// one-time animations handling
	if ((state == State::attacking) && (animations.animations[state].hasEnded())) {
		animations.animations[state].reset();
		state = State::idle;
	}
	if ((state == State::transforming) && (animations.animations[state].hasEnded())) {
		animations.animations[state].reset();
		state = State::rolling;
	}
	if ((state == State::transforming_back) && (animations.animations[state].hasEnded())) {
		animations.animations[state].reset();
		state = State::idle;
	}

	if (state == State::death && (animations.animations[state].hasEnded())) {
		animations.animations[state].reset();
		reset();
	}

	//TODO: make head stay in place when not moving
	// update animations
	
	animations.animations[state].update(dt_);
	animations.animations[state].applyToSprite(sprite, dir);
	//update position
	if (state == State::walk || state == State::rolling) {
		x += dx * dt_;	
	}
	y += dy * dt_;

	doCollisions(level.groundRects);
	if (doCollisions(level.spikeRects)) {
		death_sound.play();
		state = State::death;
	}

	sprite.setPosition(x, y);
	
	//reset velocities for next loop
	dx = 0; 
	if (!isHead)
		dy += GRAVITY * dt_;
	else
		dy += GRAVITY_HEAD * dt_;
}

bool Player::doCollisions(std::vector<sf::FloatRect> rects) {
	sf::Vector2f rectCenter;
	sf::Vector2f rectSize;
	
	sf::Vector2f playerSize(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sf::Vector2f playerCenter(x + playerSize.x, y + playerSize.y);

	bool flag = false;

	for (sf::FloatRect& rect : rects) {
		rectSize.x = rect.width / 2;
		rectSize.y = rect.height / 2;
		rectCenter.x = rect.left + rectSize.x;
		rectCenter.y = rect.top + rectSize.y;

		float deltaX = rectCenter.x - playerCenter.x;
		float deltaY = rectCenter.y - playerCenter.y;
		float intersectX = abs(deltaX) - (rectSize.x + playerSize.x);
		float intersectY = abs(deltaY) - (rectSize.y + playerSize.y);

		if (intersectX < 0.0 && intersectY < 0.0) {
			if (deltaY > 0.0) {
				isOnGround = true;
				dy = 0;
			}

			flag = true;
			if (intersectX > intersectY) {
				if (deltaX > 0.0) {
					x += intersectX;
				}
				else {
					x -= intersectX;
				}
			}
			else {
				if (deltaY > 0.0) {
					y += intersectY;
				}
				else {
					y -= intersectY;
				}
			}
		}
	}
	return flag;
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

void Player::attack(float tp_) {
	if ((state == State::attacking) || (state == State::rolling) || (state == State::transforming) || (state == State::transforming_back) || (state == State::death) || !isOnGround)
		return;

	if (tp_ >= (last_attack + attack_cd)) {
		state = State::attacking;
		last_attack = tp_;
	}
}

void Player::jump(float dt_) {
	if (state == State::death || (state == State::transforming) || (state == State::transforming_back))
		return;

	if ((!isJumping) && isOnGround) {
		isOnGround = false;
		isJumping = true;
		dy = PLAYER_DY;
	}
}

void Player::transform(float tp_) {
	if ((state == State::attacking) || (state == State::transforming) || (state == State::transforming_back) || (state == State::death) || !isOnGround)
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
