#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Animation {
public:
	typedef std::vector<sf::Texture> Frames;

	std::map<char, Frames> frames;
	sf::Texture texture;
	sf::Image image;

	Animation(const std::string path, int frame_count);
};