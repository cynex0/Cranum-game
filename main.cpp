#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Player.h"
#include <iostream>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(WINDOW_W, WINDOW_H), "SFML Works!");
	
	Player player(100, 100);

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
			player.setdX(PLAYER_DX);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player.setdX(-PLAYER_DX);
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			player.attack();
		}

		// update entities
		player.update(dt);

		// draw
		//TODO: background
		window.clear();
		//TODO: for entity in entities: entity.draw()
		window.draw(player.sprite);
		window.display();
	}

	return 0;
}
