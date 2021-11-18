#pragma once
#include "IMoveable.h"
#include <SFML/Graphics.hpp>

class Player : public IMoveable {
private:

	
	sf::Texture idle_animation[11];
	sf::Texture attack_animation[18];
	sf::Texture dead_animation[15];
	sf::Texture hit_animation[8];
	sf::Texture walk_animation[13];
	
	int lives;
	int state; // 0 - default; 1 - head

public:

	sf::Sprite sprite;
	Player(double x, double y);
	~Player();

	virtual void move();
	virtual void setdX(double dx_);
	virtual void setdY(double dy_);
};
