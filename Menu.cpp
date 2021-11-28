#include "Menu.h"
#include "Animation.h"

Menu::Menu() {
	BG.fromDir("sprites/menu", 16);
	bg_sprite.setPosition(0, 0);

	title_texture.loadFromFile("sprites/title_05x.png");
	start_texture.loadFromFile("sprites/start_btn.png");
	exit_texture.loadFromFile("sprites/exit_btn.png");

	title_sprite.setTexture(title_texture);
	start_sprite.setTexture(start_texture);
	exit_sprite.setTexture(exit_texture);

	title_sprite.setPosition(347, 24);
	start_sprite.setPosition(649, 283);
	exit_sprite.setPosition(691, 373);

	if (!buffer.loadFromFile("sprites/theme.wav")) 
		return;
	music.setBuffer(buffer);

	music.setVolume(20);
	music.play();
}

Menu::~Menu()
{
	music.stop();
}

void Menu::update(float dt_)
{
	BG.update(dt_);
}

void Menu::draw(sf::RenderWindow& window)
{
	BG.applyToSprite(bg_sprite, 'r');
	
	window.draw(bg_sprite);
	window.draw(title_sprite);
	window.draw(start_sprite);
	window.draw(exit_sprite);
}
