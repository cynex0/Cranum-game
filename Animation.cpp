#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

Animation::Animation() {
	length = 0;
}

void Animation::fromDir(const std::string path, int frame_count) {
	length = frame_count;

	for (int i = 0; i < length; ++i) {
		image.loadFromFile(path + "/frame" + std::to_string(i) + ".png");

		//dir right
		texture.loadFromImage(image);
		frames['r'].push_back(texture);

		//dir left
		image.flipHorizontally();
		texture.loadFromImage(image);
		frames['l'].push_back(texture);
	}
}

sf::Texture Animation::getTexture(char dir, int iFrame) {
	return frames[dir].at(iFrame);
}

int Animation::getLength() {
	return length;
}
