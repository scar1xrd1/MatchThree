#include <SFML/Graphics.hpp>//254 line
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

void beep(int freq, int m)
{
	Beep(freq, m);
}

class Button
{
	string sColor;

	bool pressed = false;
	int x, y;
	int current_color;
	int id;// for combinations checking
	int iColor[7][3]{ {101, 83, 172}, {188, 76, 67}, {67, 188, 76}, {193, 61, 194}, {194, 193, 61}, {61, 194, 193}, {0, 0, 0} };
	RectangleShape btn;

public:
	Button() { btn.setSize(Vector2f(100, 100)); }

	Button(int x, int y, int color, int id, int size) : current_color(color), x(x), y(y), id(id)
	{
		btn.setSize(Vector2f(size, size));
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

	int get_id() { return id; }

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
			current_color = value1;
			btn.setFillColor(Color(iColor[value1][0], iColor[value1][1], iColor[value1][2]));
		}
		else if (data == "target")
		{
			btn.setFillColor(Color(iColor[current_color][0] + 25, iColor[current_color][1] + 25, iColor[current_color][2] + 25));
		}
		else if (data == "untarget")
		{
			btn.setFillColor(Color(iColor[current_color][0], iColor[current_color][1], iColor[current_color][2]));
		}
	}

	void swap(Button& other)
	{
		int a = current_color;
		set("color", other.get_color());
		other.set("color", a);
	}

	void press(string value)
	{
		if (!pressed) set(value, 0);
	}
};

class Field
{
	Button** button;
	int x, y;
	int width, height;

	int pressed; // to move objects selected by the player
	int press[2];

	int player_point = 0; // for gameplay

public:
	Field(int width, int height) : width(width), height(height)
	{
		int size = std::min((100 / (int)pow(2, width / 13) + 2), (100 / (int)pow(2, height / 7) + 2));
		button = new Button * [height];
		for (int i = 0; i < height; i++) button[i] = new Button[width];

		thread* th = new thread[width];//threads array
		for (int i = 0; i < width; i++)
		{
			th[i] = thread([=] {
				srand(time(0) - width + (time_t)i);//this allows to asynchronise random even when a second passes while creating threads
				int x = (size + 2) * i;
				y = 0;
				for (int j = 0; j < height; j++)
				{
					button[j][i] = Button(x, y, random(0, 5), j * width + i, size);//[j][i] generates by columns
					y += (size + 2);
				}
			});//creating threads for each column generation

			th[i].join();
		}

		Clean();
	}

	int random(int a, int b) { return a + rand() % (b - a + 1); }

	void sleep(string type, int time)
	{
		if(type == "ms") this_thread::sleep_for(chrono::milliseconds(time));
		else if(type == "sec") this_thread::sleep_for(chrono::seconds(time));
	}

	void deleteButton(int id) {
		button[id / width][id % width].set("color", 6);
	}

	void draw(RenderWindow& window)
	{
		for (int i = 0; i < width; i++) for (int j = 0; j < height; j++)
			window.draw(show(j, i));
	}

	int Clean() {
		thread* th = new thread[width];
		vector<vector<Button>> verticalMatches;
		for (int i = 0; i < width; i++)
		{
			th[i] = thread([&] {

				vector<Button> column;
			column.push_back(button[0][i]);
			for (int j = 1; j < height; j++)
			{
				if (button[j][i].get_color() != column[0].get_color()) {
					if (column.size() >= 3) verticalMatches.push_back(column);
					column.clear();
				}
				column.push_back(button[j][i]);
			}
			if (column.size() >= 3) verticalMatches.push_back(column);
				});
			th[i].join();
		}

		th = new thread[height];
		vector<vector<Button>> horizontalMatches;
		for (int i = 0; i < height; i++)
		{
			th[i] = thread([&] {
				vector<Button> row;
			row.push_back(button[i][0]);
			for (int j = 1; j < width; j++)
			{
				if (button[i][j].get_color() != row[0].get_color()) {
					if (row.size() >= 3) horizontalMatches.push_back(row);
					row.clear();
				}
				row.push_back(button[i][j]);
			}
			if (row.size() >= 3) horizontalMatches.push_back(row);
				});
			th[i].join();
		}

		if (horizontalMatches.size() == 0 && verticalMatches.size() == 0) return 0;//there`s no combinations on the field

		vector<vector<Button>> specialMatches;
		if (horizontalMatches.size() == 0 || verticalMatches.size() == 0) goto empty;
		for (int i = 0; i < horizontalMatches.size(); i++)
		{
			for (int j = 0; j < horizontalMatches.at(i).size(); j++)
			{
				for (int i1 = 0; i1 < verticalMatches.size(); i1++)
				{
					for (int j1 = 0; j1 < verticalMatches.at(i1).size(); j1++)
					{
						if (horizontalMatches.at(i).at(j).get_id() == verticalMatches.at(i1).at(j1).get_id()) {//if 2 combs share the same button
							specialMatches.push_back(horizontalMatches.at(i));
							for (int k = 0; k < verticalMatches.at(i1).size(); k++)
							{
								specialMatches.back().push_back(verticalMatches.at(i1).at(k));
							}
							horizontalMatches.erase(horizontalMatches.begin() + i);
							verticalMatches.erase(verticalMatches.begin() + i1);
							if (horizontalMatches.size() == 0 || verticalMatches.size() == 0) goto empty;
						}
					}
				}
			}
		}
	empty:
		future<void> hdelete = async(launch::async, [&] {
			if (horizontalMatches.size() > 0) 
				for (int i = 0; i < horizontalMatches.size(); i++)
					for (int j = 0; j < horizontalMatches.at(i).size(); j++)
						deleteButton(horizontalMatches.at(i).at(j).get_id());
			});

		future<void> vdelete = async(launch::async, [&] {
			if (verticalMatches.size() > 0) 
				for (int i = 0; i < verticalMatches.size(); i++)
					for (int j = 0; j < verticalMatches.at(i).size(); j++)
						deleteButton(verticalMatches.at(i).at(j).get_id());
			});

		future<void> sdelete = async(launch::async, [&] {
			if (specialMatches.size() > 0) 
				for (int i = 0; i < specialMatches.size(); i++)
					for (int j = 0; j < specialMatches.at(i).size(); j++)
						deleteButton(specialMatches.at(i).at(j).get_id());
			});
		hdelete.get();
		vdelete.get();
		sdelete.get();
		
		gapFill(); //cout << "gapFill ended!" << endl;
		Clean();

		return verticalMatches.size() + horizontalMatches.size() + specialMatches.size() * 2;
	}

	void gapFill() {
		future<void>* th = new future<void>[width]; //cout << this_thread::get_id() << endl;

		for (int i = 0; i < width; i++)
		{
			sleep("ms", 1);
			th[i] = async(launch::async, [&] {
				int i1 = i;
				srand(time(0) - width + (time_t)i1);
				bool finish = false;
				int tempColor;
				if (button[0][i1].get_color() == 6) button[0][i1].set("color", random(0, 5));
				while (!finish) {
					finish = true;
					for (int j = height - 1; j > 0; j--) {
						if (finish && button[j][i1].get_color() == 6) finish = false;
						if (!finish) { //move one tile down
							button[j][i1].set("color", button[j - 1][i1].get_color());
							button[j - 1][i1].set("color", 6);//black
						} //cout << "column " << i1 << " moved" << endl;
					
					}
					if (!finish) button[0][i1].set("color", random(0, 5));
				}
			}); //cout << "thread " << i << " ended" << endl;
			sleep("ms", 1);
		}
		for (int i = 0; i < width; i++) th[i].get();
	}

	void buttonPress(int x, int y)
	{
		int clean = 0;

		if (pressed++ == 0) // click first button
		{
			button[x][y].press("target");
			press[0] = x; press[1] = y;			
		}
		else // click second button
		{
			button[x][y].press("target");
			button[x][y].swap(button[press[0]][press[1]]);
			button[x][y].press("untarget");
			button[press[0]][press[1]].press("untarget");
			pressed = 0;

			bool stop;

			if (button[x][y].get_id() / width == button[press[0]][press[1]].get_id() / width && abs(button[x][y].get_id() % width - button[press[0]][press[1]].get_id() % width) == 1 || abs(button[x][y].get_id() - button[press[0]][press[1]].get_id()) == width) stop = false;
			else stop = true;
			
			if (!stop) clean = Clean();

			if (clean == 0) // if no combinations
			{	
				button[x][y].swap(button[press[0]][press[1]]);
				thread th1(beep, 500, 100); thread th2(beep, 300, 100);
				th1.detach(); th2.detach();
			}
			else // else if have combintions
			{
				player_point += clean;
				thread th1(beep, 750, 100); thread th2(beep, 800, 100);
				th1.detach(); th2.detach();
			}

			system("cls");
			cout << "PLAYER POINT\t" << player_point << "\n";
		}
	}

	RectangleShape show(int x, int y) { return button[x][y].show(); }
};

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