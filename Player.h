#pragma once
#include "IMoveable.h"
#include "AnimationManager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Player : public IMoveable {
private:
	AnimationManager animations;
	
	int lives;
	int last_attack; 
	int last_transform;
	const int attack_cd;
	const int transform_cd;
	char dir;

public:
	bool isHead;
	State state;
	sf::Sprite sprite;

	Player(double x, double y);
	~Player();

	virtual void update(int dt_);
	virtual void draw(sf::RenderWindow& window);
	virtual void setdX(double dx_);
	virtual void setdY(double dy_);
	void attack(int tp_);
	void transform(int tp_);
};
