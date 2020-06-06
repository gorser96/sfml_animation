#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include <math.h>
#include "VectorHelper.h"
#include "Menu.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Animations");
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);

	Menu menu("images\\menu_btn.png");

	sf::Clock clock;

	AnimatedSprite aSprite("images\\tomato_128_128.png", sf::IntRect(0, 0, 128, 128), 0, 5);
	aSprite.setScale(sf::Vector2f(0.1, 0.1));

	sf::Vector2u wSize = window.getSize();

	//П.С. тут локальные координаты
	aSprite.setPosition(sf::Vector2f(wSize.x / 2, wSize.y / 2));

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		menu.update(window);

		if (clock.getElapsedTime().asMilliseconds() > 10.0f)
		{
			//П.С. тут получаем локальные координаты мыши
			/*
			sf::Vector2i mgPos = sf::Mouse::getPosition(window);
			sf::Vector2f mlPos = window.mapPixelToCoords(mgPos);
			sf::Vector2f slPos = aSprite.getLocalPosition();
			*/

			aSprite.move(sf::Vector2f(-1, -1));

			clock.restart();
		}

		// clear the window with black color
		window.clear();

		// draw everything here...
		window.draw(aSprite.getSprite());
		menu.draw(window);

		// end the current frame
		window.display();
	}
	return 0;
}