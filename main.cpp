#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "Field.h"
#include <iostream>
using namespace std;
using namespace sf;

void beep(int freq, int m) { Beep(freq, m); }

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(0));

	int fieldWidth = 13;
	int fieldHeight = 6;

	int size = std::min((100 / (int)pow(2, fieldWidth / 13) + 2), (100 / (int)pow(2, fieldHeight / 7) + 2));
	RenderWindow window(VideoMode(fieldWidth * (size + 2) - 2, fieldHeight * (size + 2) - 2), "MatchThree");

	Field field(fieldWidth, fieldHeight);

	while (window.isOpen())
	{
		Event event;
		Vector2i mousePos = Mouse::getPosition(window);

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (mousePos.x % (size + 2) <= 50 && mousePos.y % (size + 2) <= 50) {
					thread th(beep, 666, 100);
					th.detach();
					field.buttonPress(mousePos.y / (size + 2), mousePos.x / (size + 2));
				}
			}
		}
		
		window.clear();

		for (int i = 0; i < fieldWidth; i++) for (int j = 0; j < fieldHeight; j++)
			window.draw(field.show(j, i)); 

		window.display();
	}
}