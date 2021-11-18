#pragma once
class IMoveable {
protected:
	double x, y;
	double dx, dy;
public:
	virtual void move() = 0;
};