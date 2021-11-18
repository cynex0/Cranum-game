#pragma once
#include "Player.h"
#include "Enemy.h"

class Game {
private:
	Player player;
	Enemy[] enemies;
public:
	void drawAll();

};