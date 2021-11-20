#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Animation {
private:
	typedef std::vector<sf::Texture> Frames;
	
	sf::Texture texture;
	sf::Image image;

	int length;
public:
	std::map<char, Frames> frames;
	Animation();
	void fromDir(const std::string path, int frame_count);
	sf::Texture getTexture(char dir, int iFrame);
	int getLength();
};