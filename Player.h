#pragma once
#include "IMoveable.h"
#include "Level.h"
#include "AnimationManager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Player : public IMoveable {
private:
	AnimationManager animations;
	
	bool doCollisions(std::vector<sf::FloatRect> rects);

	int lives;
	float last_attack; 
	float last_transform;
	const float attack_cd;
	const float transform_cd;
	char dir;

public:
	bool isHead;
	bool isOnGround;
	bool isJumping;
	State state;
	sf::Sprite sprite;

	Player(double x, double y);
	~Player();

	virtual void update(float dt_, Level& level, sf::RenderWindow& window);
	virtual void draw(sf::RenderWindow& window);
	virtual void setdX(double dx_);
	virtual void setdY(double dy_);
	void reset();
	void attack(float tp_);
	void jump(float dt_);
	void transform(float tp_);
};
