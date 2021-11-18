#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Player.h"

using namespace sf;

int main()
{
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
		//update entities
		player.move();

		//draw
		window.clear();
		window.draw(player.sprite);
		window.display();
	}

	return 0;
}
