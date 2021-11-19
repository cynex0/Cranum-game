#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

Animation::Animation(const std::string path, int frame_count) {
	for (int i = 0; i < frame_count; ++i) {
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