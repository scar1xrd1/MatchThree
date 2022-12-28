#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include <iostream>
using namespace std;
using namespace sf;

class Field
{
	Button** button; // button parameters
	int x, y;
	int width, height;

	int pressed; // to move objects selected by the player
	int press[2];

	int player_point = 0; // for gameplay

public:
	Field(int width, int height);

	void beep(int freq, int m) { Beep(freq, m); }
	int random(int a, int b) { return a + rand() % (b - a + 1); }
	void sleep(string type, int time);

	void deleteButton(int id) { button[id / width][id % width].set("color", 6); }
	int Clean();
	void gapFill();

	void buttonPress(int x, int y);

	RectangleShape show(int x, int y) { return button[x][y].show(); }
};