#include "Player.h"
#include <SFML/Graphics.hpp>


Player::Player(double x_, double y_) {
	x = x_;
	y = y_;
	dx = 0;
	dy = 0;
	lives = 3;
	state = 0;

	texture.loadFromFile("sprites/player/idle/frame0.png");
	sprite.setTexture(texture);
}

Player::~Player() {}

void Player::move() {
	x += dx;
	y += dy;
	sprite.setPosition(x, y);
}