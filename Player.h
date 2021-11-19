#pragma once
#include "IMoveable.h"
#include "Animation.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Player : public IMoveable {
private:
	sf::Clock playerClock;

//TODO : map["right", "left"]
	Animation idle_animation;
	sf::Texture attack_animation[18];
	sf::Texture dead_animation[15];
	sf::Texture hit_animation[8];
	Animation walk_animation;
	
	int lives;
	int state; // 0 - default; 1 - head
	int anim_time;
	int current_frame;
	char dir;

	enum Anim_Type { idle, walk, jump };
	Anim_Type anim = idle;

public:
	sf::Sprite sprite;
	Player(double x, double y);
	~Player();

	virtual void update(int dt_);
	virtual void draw(sf::RenderWindow window);
	virtual void setdX(double dx_);
	virtual void setdY(double dy_);
};
