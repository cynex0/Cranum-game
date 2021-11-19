#pragma once
#include "IMoveable.h"
#include "Animation.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Player : public IMoveable {
private:
	sf::Clock playerClock;

	Animation idle_animation;
	Animation walk_animation;
	Animation attack_animation;
	Animation death_animation;
	Animation hit_animation;	
	
	int lives;
	int anim_time;
	int current_frame;
	char dir;

	enum State { idle, walk, jump, attack, take_dmg, death };
	State state;

public:
	sf::Sprite sprite;
	Player(double x, double y);
	~Player();

	virtual void update(int dt_);
	virtual void draw(sf::RenderWindow window);
	virtual void setdX(double dx_);
	virtual void setdY(double dy_);
};
