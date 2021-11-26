#pragma once
#include "constants.h"
#include <list>
#include <SFML/Graphics.hpp>


class Level {
private:
	sf::Texture texture;
	sf::Sprite sprite;

	int map[TILES_X][TILES_Y];
	std::list<sf::Sprite> sprite_map;

public:
	Level(int id);
	void getSprites();
	void draw(sf::RenderWindow& window);
};