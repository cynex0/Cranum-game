#pragma once
class IMoveable {
protected:
	double x, y;
	double dx, dy;
public:
	virtual void move() = 0;
	virtual void setdX(double dx_) = 0;
	virtual void setdY(double dy_) = 0;
};
