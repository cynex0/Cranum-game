#pragma once
#include <SFML/Graphics.hpp>

class IMoveable {
protected:
	double x, y;
	double dx, dy;

public:
	enum State { idle, walk, jump, attacking, take_dmg, death };

	virtual void update(int dt_) = 0;
	virtual void draw(sf::RenderWindow window) = 0;
	virtual void setdX(double dx_) = 0;
	virtual void setdY(double dy_) = 0;
};
