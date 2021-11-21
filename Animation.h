#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class Animation {
private:
	typedef std::vector<sf::Texture> Frames;
	std::map<char, Frames> frames;
	
	sf::Texture texture;
	sf::Image image;

	int length;
	int iFrame;
	double frameTime;
	double time;

	void advance();

public:
	Animation();
	void fromDir(const std::string path, int frame_count);
	void applyToSprite(sf::Sprite& sprite, char dir);
	int getLength();
	void update(float dt_);
	bool hasEnded();
	void reset();
};