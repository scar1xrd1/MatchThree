#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>
#include <thread>
#include <ctime>
#include <chrono>
#include <mutex>
#include <future>
using namespace std;
using namespace sf;

class Button
{
	string sColor;
	int current_color;
	int iColor[7][3]{ {101, 83, 172}, {188, 76, 67}, {67, 188, 76}, {193, 61, 194}, {194, 193, 61}, {61, 194, 193}, {0, 0, 0} };

	bool pressed = false;
	int x, y;

	int id;// for combinations checking

	RectangleShape btn; // button

public:
	Button() { btn.setSize(Vector2f(100, 100)); }
	Button(int x, int y, int color, int id, int size);

	int get_xy(string value);
	int get_color() { return current_color; }
	int get_id() { return id; }

	void set(string data, int value1, int value2);
	void set(string data, int value1);

	void swap(Button& other);
	void press(string value);

	RectangleShape show() { return btn; }
};