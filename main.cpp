#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "Field.h"
#include "Text.h"

#include "Objects.h"
#include "NavigationMenu.h"
#include "LoadMenu.h"
#include "RefreshMenu.h"

#include <iostream>
#include <fstream>

void beep(int freq, int m) { Beep(freq, m); }

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
				return -1;
				break;

			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left) {
					if(navMenu.navigation(window) == -1) return -1;
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
	return n;
}

int GameMenu(int level)
{
	int state = 0;
	bool win, lose, stop;
	stop = win = lose = false;
	int fieldWidth = 13;
	int fieldHeight = 6;

	int lvl_score, lvl_moves;

	int size = std::min((100 / (int)pow(2, fieldWidth / 13) + 2), (100 / (int)pow(2, fieldHeight / 7) + 2));
	RenderWindow window(VideoMode(fieldWidth * (size + 2) - 2, fieldHeight * (size + 12) - 2), "MatchThree");
	
	switch (level)
	{
	case 1:
		lvl_moves = 5;
		lvl_score = 10;
		break;
	case 2:
		lvl_moves = 7;
		lvl_score = 15;
		break;
	case 3:
		lvl_moves = 5;
		lvl_score = 15;
		break;
	case 4:
		lvl_moves = 5;
		lvl_score = 20;
		break;
	case 5:
		lvl_moves = 7;
		lvl_score = 25;
		break;
	case 6:
		lvl_moves = 7;
		lvl_score = 25;
		break;
	case 7:
		lvl_moves = 3;
		lvl_score = 10;
		break;
	case 8:
		lvl_moves = 4;
		lvl_score = 15;
		break;
	case 9:
		lvl_moves = 20;
		lvl_score = 50;
		break;
	case 10:
		lvl_moves = 15;
		lvl_score = 35;
		break;
	}

	Field field(fieldWidth, fieldHeight, lvl_moves, lvl_score);

	string score, rightAmount, move, levelS;

	Texts text1(5, 320, 0, 24);
	Texts text2(5, 350, 0, 24);
	Texts moves(225, 325, 0, 34);
	Texts levelT(525, 325, 0, 34);

	while (window.isOpen() || stop)
	{
		Event event;
		Vector2i mousePos = Mouse::getPosition(window);

		while (window.pollEvent(event) || stop)
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return -1;
			}

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
		levelS = to_string(n);

		window.clear();

		for (int i = 0; i < fieldWidth; i++) for (int j = 0; j < fieldHeight; j++)
			window.draw(field.show(j, i));

		text1.set("your score " + score);
		text2.set("you need " + rightAmount);
		moves.set("your moves " + move);
		levelT.set("level " + levelS);
		window.draw(text1.show());
		window.draw(text2.show());
		window.draw(moves.show());
		window.draw(levelT.show());

		window.display();

		if (win)
		{
			window.clear();
			if (n + 1 == 11)
			{
				text1.set("END GAME");
				text2.set("YOU WIN");
				moves.set("GOOD LUCK");
			}
			else 
			{
				text1.set("YOU WIN");
				text2.set("NEXT LEVEL");
				moves.set("YOU WIN");
			}
			
			window.draw(text1.show());
			window.draw(text2.show());
			window.draw(moves.show());
			window.draw(levelT.show());
			window.display();

			beep(500, 250);
			beep(750, 250);
			beep(1000, 1000);
			if(n+1 == 11) this_thread::sleep_for(chrono::milliseconds(1000));
			else this_thread::sleep_for(chrono::milliseconds(200));
			window.close();
			if(n+1 != 11) n += 1;
			ofstream f("data/level.txt");
			f << to_string(n);
			f.close();
			if(n+1 == 11) return -1;
			return 0;
		}
		else if (lose)
		{
			window.clear();
			text1.set("YOU LOSE");
			text2.set("TRY AGAIN");
			moves.set("YOU LOSE");
			window.draw(text1.show());
			window.draw(text2.show());
			window.draw(moves.show());
			window.display();

			beep(1000, 250);
			beep(750, 250);
			beep(500, 1000);
			this_thread::sleep_for(chrono::milliseconds(200));
			window.close();
			return 0;
		}
	}
	return 0;
}

int main(){
	system("chcp 1251");
	system("cls");
	srand(time(0));

	int on = 0;

	bool start = true;
	while (start)
	{
		cout << "N " << n << endl;
		if (on++ == 0) if (MainMenu() == -1) break;		
		if (GameMenu(n) == -1) break;
	}
}