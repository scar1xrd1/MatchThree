#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <string> 
using namespace std;
#include "Objects.h";
#include "NavigationMenu.h";
#include "LoadMenu.h";
#include "RefreshMenu.h";

int MainMenu() {

	RenderWindow  window(VideoMode(600, 600), "Match Three");

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	NavMenu navMenu;

	LoadMenu(window);

	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {

			switch (event.type) {

			case Event::Closed:
				window.close();
				cout << "Window Closed!" << endl;
				break;

			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left) {

					navMenu.navigation(window);
				}
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Key::Escape) {
					window.clear(Color(77, 58, 90));
					RefreshMenu(window);
					window.display();

				}

			default:
				break;
			}
		}
	}
	return 0;
}