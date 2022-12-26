#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <ctime>
#include <chrono>
using namespace std;
using namespace sf;

class Button
{
	string sColor;

	int x, y;
	int current_color;
	//int iColor[6][3] = { {255,0,0}, {95,0,0}, {250,128,114}, {178,34,34}, {205,92,92}, {220,20,60} };
	int iColor[6][3]{ {101, 83, 172}, {188, 76, 67}, {67, 188, 76}, {193, 61, 194}, {194, 193, 61}, {61, 194, 193} };
	RectangleShape btn;

public:
	Button() { btn.setSize(Vector2f(100, 100)); }

	Button(int x, int y, int color) : current_color(color), x(x), y(y)
	{
		btn.setSize(Vector2f(100, 100));
		btn.setFillColor(Color(iColor[color][0], iColor[color][1], iColor[color][2]));
		btn.setPosition(x, y);
	}

	RectangleShape show() { return btn; }

	int get_xy(string value)
	{
		if (value == "x") return x;
		if (value == "y") return y;
	}
	
	int get_color() { return current_color; }

	void set(string data, int value1, int value2)
	{
		if (data == "xy")
		{
			x = value1; y = value2;
			btn.setPosition(x, y);
		}
	}
	
	void set(string data, int value1)
	{
		if (data == "color")
		{
			btn.setFillColor(Color(iColor[value1][0], iColor[value1][1], iColor[value1][2]));
		}
	}

	void swap(Button& other)
	{

	}
};

class Field
{
	Button button[6][6];
	int x, y;

public:
	Field(int width, int height)
	{
		srand(time(0));

		x = 0;
		for (int i = 0; i < width; i++)
		{			
			y = 0;
			for (int j = 0; j < height; j++)
			{				
				button[i][j] = Button(x, y, 0 + rand() % (5 + 1));
				y += 102;
			}
			x += 102;
		}

		/*Button buffer(5000, 5000, 0);

		button[0][0] = Button(0, 0, 5);
		button[1][0] = Button(102, 0, 2);
		button[2][0] = Button(204, 0, 5);


		ДОДЕЛАТЬ !!!!!!!!!!!!!!!!!! ДОДЕЛАТь

		buffer.set("xy", button[0][0].get_xy("x"), button[0][0].get_xy("y"));
		buffer.set("color", button[0][0].get_color());

		cout << button[0][0].get_color() << endl;

		button[0][0] = Button(button[1][0].get_xy("x"), button[1][0].get_xy("y"), button[1][0].get_color());

		button[1][0] = Button(buffer.get_xy("x"), buffer.get_xy("y"), buffer.get_color());*/
	}

	RectangleShape show(int x, int y) { return button[x][y].show(); }
};

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(0));
	RenderWindow window(VideoMode(610, 610), "MatchThree");

	Field field(6, 6);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}

		window.clear();

		for (int i = 0; i < 6; i++) for (int j = 0; j < 6; j++)
			window.draw(field.show(i, j));

		window.display();
	}	
}