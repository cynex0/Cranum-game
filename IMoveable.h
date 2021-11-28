#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

class IMoveable {
protected:
	double x, y;
	double init_x, init_y;
	double dx, dy;

public:
	enum State { idle, walk, attacking, take_dmg, death, transforming, transforming_back, rolling };

	virtual void update(float dt_, Level& level, sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void setdX(double dx_) = 0;
	virtual void setdY(double dy_) = 0;
};
