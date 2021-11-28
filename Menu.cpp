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

	start_rect.left = start_sprite.getPosition().x;
	start_rect.top = start_sprite.getPosition().y;
	start_rect.width = start_texture.getSize().x;
	start_rect.height = start_texture.getSize().y;
	
	exit_rect.left = exit_sprite.getPosition().x;
	exit_rect.top = exit_sprite.getPosition().y;
	exit_rect.width = exit_texture.getSize().x;
	exit_rect.height = exit_texture.getSize().y;

	if (!buffer.loadFromFile("sprites/theme.wav")) 
		return;
	music.setBuffer(buffer);

	music.setVolume(15);
	music.setLoop(true);
	music.play();
}

Menu::~Menu(){}

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

void Menu::stop()
{
	music.stop();
}

sf::IntRect Menu::getStartBtn()
{
	return start_rect;
}

sf::IntRect Menu::getExitBtn()
{
	return exit_rect;
}
