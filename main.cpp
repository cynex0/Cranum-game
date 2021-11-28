#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "constants.h"
#include "Player.h"
#include "Level.h"
#include "Menu.h"
#include <list>
#include <iostream>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(WINDOW_W, WINDOW_H), "Cranum");

	Level levels[3] = { Level(1), Level(2), Level(3)};
	int current_level_id = 0;

	sf::SoundBuffer buffer;
	sf::Sound level_music;
	if (buffer.loadFromFile("sprites/level_music.wav")) {
		level_music.setBuffer(buffer);

		level_music.setVolume(15);
		level_music.setLoop(true);
	}
	

	Player player(100, 100);
	enum GameStates {menu, game};
	GameStates state = menu;
	Menu title_screen;
	Vector2i mousePos;

	Texture bg_texture;
	bg_texture.loadFromFile("sprites/BG.png");
	Sprite bg(bg_texture);

	sf::Clock clock;
	clock.restart();
	float tp = clock.getElapsedTime().asMilliseconds() / 1000.0;
	float dt = 0;
	float new_tp = 0;

	// game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return 0;
			}
		}
		// get frame time
		new_tp = clock.getElapsedTime().asMilliseconds() / 1000.0;
		dt = new_tp - tp;
		if (dt > 0.15)
			dt = 0.15;
		tp = new_tp;

		if (levels[current_level_id].isCompleted)
		{		
			if (++current_level_id < 3) {
				player.reset();
			}
			else {
				window.close();
				return 0;
			}
		}

		switch (state)
		{
		case menu:
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				mousePos = Mouse::getPosition(window);
				if (title_screen.getStartBtn().contains(mousePos)) {
					state = game;
					title_screen.stop();
					level_music.play();
				}
				if (title_screen.getExitBtn().contains(mousePos)) {
					window.close();
					title_screen.stop();
					return 0;
				}
			}

			title_screen.update(dt);
			title_screen.draw(window);
			break;

		case game:
			// input
			if (player.isHead && Keyboard::isKeyPressed(Keyboard::Up)) {
				player.jump(dt);
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				player.setdX(PLAYER_DX + (DX_BUFF * player.isHead)); // player gets a speed buff when in head form
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				player.setdX(-PLAYER_DX - (DX_BUFF * player.isHead));
			}
			/*if (Keyboard::isKeyPressed(Keyboard::Space)) {
				player.attack(tp);
			}*/
			if (Keyboard::isKeyPressed(Keyboard::LShift)) {
				player.transform(tp);
			}

			// update entities
			player.update(dt, levels[current_level_id], window);

			// draw
			window.clear();
			window.draw(bg);
			levels[current_level_id].draw(window);
			player.draw(window);
			break;
		}
		
		window.display();
	}	
	return 0;
}
