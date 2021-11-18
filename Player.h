#pragma once
#include "IMoveable.h"
#include <SFML/Graphics.hpp>

class Player : public IMoveable {
private:
	sf::Texture texture;
	int lives;
	int state; // 0 - default; 1 - head

public:
	sf::Sprite sprite;
	Player(double x, double y);
	~Player();

	virtual void move();
};