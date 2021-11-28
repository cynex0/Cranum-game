#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"

class Menu {
private:
	Animation BG;

	sf::Sprite bg_sprite;
	sf::Sprite title_sprite;
	sf::Sprite start_sprite;
	sf::Sprite exit_sprite;

	sf::Texture title_texture;
	sf::Texture start_texture;
	sf::Texture exit_texture;

	sf::SoundBuffer buffer;
	sf::Sound music;

public:
	Menu();
	~Menu();
	void update(float dt_);
	void draw(sf::RenderWindow& window);
};