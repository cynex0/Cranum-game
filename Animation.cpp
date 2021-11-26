#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <string>

Animation::Animation(){
	frameTime = 60;
	length = 0;
	time = 0;
	iFrame = 0;
}

void Animation::fromDir(const std::string path, int frame_count) {
	if (frame_count > 0) {
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
	// reverse animation
	else if (frame_count < 0) {
		length = -frame_count;
		for (int i = 0; i < length; ++i) {
			image.loadFromFile(path + "/frame" + std::to_string(length - i - 1) + ".png");

			//dir right
			texture.loadFromImage(image);
			frames['r'].push_back(texture);

			//dir left
			image.flipHorizontally();
			texture.loadFromImage(image);
			frames['l'].push_back(texture);
		}
	}
}

void Animation::applyToSprite(sf::Sprite& sprite, char dir) {
	sprite.setTexture(this->frames[dir].at(iFrame));
}

int Animation::getLength() {
	return length;
}

void Animation::update(float dt_) {
	time += dt_;
	while (time >= frameTime) {
		time -= frameTime;
		advance();
	}
}

void Animation::advance() {
	iFrame++;
	if (iFrame >= length) {
		iFrame = 0;
	}
}

bool Animation::hasEnded() {
	return (iFrame >= (length - 1));
}

void Animation::reset() {
	time = 0;
	iFrame = 0;
}

