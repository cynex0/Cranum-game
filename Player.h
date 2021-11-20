#pragma once
#include "IMoveable.h"
#include "AnimationManager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Player : public IMoveable {
private:
	sf::Clock playerClock;
	AnimationManager animations;
	Animation current_animation;
	
	int lives;
	int anim_time;
	int current_frame;
	int last_attack;
	char dir;

	State state;

public:
	sf::Sprite sprite;
	Player(double x, double y);
	~Player();

	virtual void update(int dt_);
	virtual void draw(sf::RenderWindow window);
	virtual void setdX(double dx_);
	virtual void setdY(double dy_);
	void attack();
};
