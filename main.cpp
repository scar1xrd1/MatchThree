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

	bool stop = false;
	int fieldWidth = 13;
	int fieldHeight = 6;

	int size = std::min((100 / (int)pow(2, fieldWidth / 13) + 2), (100 / (int)pow(2, fieldHeight / 7) + 2));
	RenderWindow window(VideoMode(fieldWidth * (size + 2) - 2, fieldHeight * (size + 12) - 2), "MatchThree");

	Field field(fieldWidth, fieldHeight, 5, 10);

	Font font;
	Text text1;
	Text text2;

	string score, rightAmount;

	text1.setFont(font);
	text1.setPosition(5, 325);
	text1.setFillColor(Color::White);
	text1.setCharacterSize(34);
	
	text2.setFont(font);
	text2.setPosition(325, 325);
	text2.setFillColor(Color::White);
	text2.setCharacterSize(34);

	if (!font.loadFromFile("fonts/LucidaTypewriterBold.ttf"))
	{
		cout << "Error load font\n";
	}

	while (window.isOpen() || stop)
	{
		Event event;
		Vector2i mousePos = Mouse::getPosition(window);
		score = field.getScore();
		rightAmount = field.getRightAmount();

		while (window.pollEvent(event) || stop)
		{
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (mousePos.x % (size + 2) <= 50 && mousePos.y % (size + 2) <= 50) {					
					if (field.buttonPress(mousePos.y / (size + 2), mousePos.x / (size + 2)) == 1) window.close();
				}
			}
		}
		
		window.clear();

		for (int i = 0; i < fieldWidth; i++) for (int j = 0; j < fieldHeight; j++)
			window.draw(field.show(j, i)); 

		text1.setString("your score " + score);
		text2.setString("you need " + rightAmount);
		window.draw(text1);
		window.draw(text2);

		window.display();
	}
}