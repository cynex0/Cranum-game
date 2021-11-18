#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Player.h"
#include <iostream>

using namespace sf;

int main()
{
	sf::Clock clock;

	RenderWindow window(VideoMode(WINDOW_W, WINDOW_H), "SFML Works!");
	
	Player player(100, 100);

	//game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();	
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			//std::cout << "Right" << std::endl;
			player.setdX(PLAYER_DX);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			//std::cout << "left" << std::endl;
			player.setdX(-PLAYER_DX);
		}

		//update entities
		player.move();

		//draw
		window.clear();
		window.draw(player.sprite);
		window.display();
	}

	return 0;
}
