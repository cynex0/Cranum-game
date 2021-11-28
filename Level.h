#pragma once
#include "constants.h"
#include <vector>
#include <SFML/Graphics.hpp>


class Level {
private:
	int id;

	sf::Texture texture;
	sf::Sprite sprite;

	std::vector<sf::Sprite> sprite_map;

public:
	bool isCompleted;

	std::vector<std::vector<int>> map;

	std::vector<sf::FloatRect> groundRects;
	std::vector<sf::FloatRect> spikeRects;

	Level(int id_);
	void draw(sf::RenderWindow& window);
};