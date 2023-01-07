﻿#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "Field.h"
#include "Text.h"
#include <iostream>
using namespace std;
using namespace sf;

void beep(int freq, int m) { Beep(freq, m); }

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(0));

	int state = 0;
	bool win, lose, stop;
	stop = win = lose = false;
	int fieldWidth = 13;
	int fieldHeight = 6;

	int size = std::min((100 / (int)pow(2, fieldWidth / 13) + 2), (100 / (int)pow(2, fieldHeight / 7) + 2));
	RenderWindow window(VideoMode(fieldWidth * (size + 2) - 2, fieldHeight * (size + 12) - 2), "MatchThree");

	Field field(fieldWidth, fieldHeight, 5, 10);

	string score, rightAmount, move;

	Texts text1(5, 320, 0, 24);
	Texts text2(5, 350, 0, 24);
	Texts moves(200, 325, 0, 34);

	while (window.isOpen() || stop)
	{
		Event event;
		Vector2i mousePos = Mouse::getPosition(window);

		while (window.pollEvent(event) || stop)
		{
			if (event.type == Event::Closed) window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (mousePos.x % (size + 2) <= 50 && mousePos.y % (size + 2) <= 50) {					
					state = field.buttonPress(mousePos.y / (size + 2), mousePos.x / (size + 2));
					if (state == 1) win = true;
					else if (state == 2) lose = true;
				}
			}
		}
		
		score = field.getScore();
		rightAmount = field.getRightAmount();
		move = field.getMove();

		window.clear();

		for (int i = 0; i < fieldWidth; i++) for (int j = 0; j < fieldHeight; j++)
			window.draw(field.show(j, i)); 

		text1.set("your score " + score);
		text2.set("you need " + rightAmount);
		moves.set("your moves " + move);
		window.draw(text1.show());
		window.draw(text2.show());
		window.draw(moves.show());

		window.display();

		if(win) 
		{
			beep(500, 250);
			beep(750, 250);
			beep(1000, 1000);
			this_thread::sleep_for(chrono::milliseconds(200));
			window.close();
		}
		else if (lose)
		{
			beep(1000, 250);
			beep(750, 250);
			beep(500, 1000);
			this_thread::sleep_for(chrono::milliseconds(200));
			window.close();
		}
	}
}