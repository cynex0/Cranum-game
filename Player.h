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
	int last_attack; 
	int last_transform;
	int jump_time;
	const int attack_cd;
	const int transform_cd;
	char dir;

public:
	bool isHead;
	bool isOnGround;
	bool isJumping;
	State state;
	sf::Sprite sprite;

	Player(double x, double y);
	~Player();

	virtual void update(int dt_, Level& level, sf::RenderWindow& window);
	virtual void draw(sf::RenderWindow& window);
	virtual void setdX(double dx_);
	virtual void setdY(double dy_);
	void reset();
	void attack(int tp_);
	void jump(int tp_);
	void transform(int tp_);
};
