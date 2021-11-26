﻿#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Player.h"
#include "Level.h"
#include <vector>
#include <iostream>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(WINDOW_W, WINDOW_H), "SFML Works!");
	
	Level level = Level(1);
	int current_level = 1;

	Player player(100, 100);

	Texture bg_texture;
	bg_texture.loadFromFile("sprites/BG.png");
	Sprite bg(bg_texture);

	sf::Clock clock;
	clock.restart();
	int tp = clock.getElapsedTime().asMilliseconds();
	int dt = 0;
	int new_tp = 0;

	// game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();	
		}

		// get frame time
		new_tp = clock.getElapsedTime().asMilliseconds();
		dt = new_tp - tp;
		tp = new_tp;

		// input
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player.setdX(PLAYER_DX + (DX_BUFF * player.isHead)); // player gets a speed buff when in head form
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player.setdX(-PLAYER_DX - (DX_BUFF * player.isHead));
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			player.attack(tp);
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift)) {
			player.transform(tp);
		}

		// update entities
		player.update(dt);

		// draw
		window.clear();
		//TODO: for entity in entities: entity.draw()
		window.draw(bg);
		level.draw(window);
		player.draw(window);
		window.display();
	}

	return 0;
}
