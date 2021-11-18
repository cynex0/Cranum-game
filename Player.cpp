#include "Player.h"
#include <SFML/Graphics.hpp>


Player::Player(double x_, double y_) {
	x = x_;
	y = y_;
	dx = 0;
	dy = 0;
	lives = 3;
	state = 0;

	for (int i = 0; i < 11; i++) {
		idle_animation[i].loadFromFile("sprites/player/idle/frame"+ i + ".png");
	}

	for (int i = 0; i < 18; i++) {
		attack_animation[i].loadFromFile("sprites/player/attack/frame" + i + ".png");
	}

	for (int i = 0; i < 15; i++) {
		dead_animation[i].loadFromFile("sprites/player/dead/frame" + i + ".png");
	}

	for (int i = 0; i < 8; i++) {
		hit_animation[i].loadFromFile("sprites/player/hit/frame" + i + ".png");
	}

	for (int i = 0; i < 13; i++) {
		walk_animation[i].loadFromFile("sprites/player/walk/frame" + i + ".png");
	}

}

Player::~Player() {}

void Player::move() {
	x += dx;
	y += dy;
	sprite.setPosition(x, y);
}