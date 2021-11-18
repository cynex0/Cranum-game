#pragma once
#include "IMoveable.h"
#include <SFML/Graphics.hpp>

class Enemy : public IMoveable {
private:


	sf::Texture idle_animation[11];
	sf::Texture attack_animation[18];
	sf::Texture dead_animation[15];
	sf::Texture hit_animation[8];
	sf::Texture walk_animation[13];

	int lives;

public:

	sf::Sprite sprite;
	Enemy(double x, double y);
	~Enemy();

	virtual void move();
};