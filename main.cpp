#include <SFML/Graphics.hpp>//254 line
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

	bool pressed = false;
	int x, y;
	int current_color;
	int id;// for combinations checking
	//int iColor[6][3] = { {255,0,0}, {95,0,0}, {250,128,114}, {178,34,34}, {205,92,92}, {220,20,60} };
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
	//Button button[6][6];
	int x, y;
	int width, height;

	int pressed; // to move objects selected by the player
	int press[2];

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
		//for a test
		/*button[0][0].set("color", 0);
		button[1][0].set("color", 0);
		button[2][0].set("color", 0);
		button[0][1].set("color", 0);
		button[0][2].set("color", 0);
		button[0][3].set("color", 2);
		button[0][3].swap(button[0][2]);*/
		Clean();

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

	int random(int a, int b) { return a + rand() % (b - a + 1); }

	void deleteButton(int id) {
		button[id / width][id % width].set("color", 6);
	}

	void Clean() {

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
		/*cout << "vertical: " << endl;
		for (int i = 0; i < verticalCombs.size(); i++) {
			for (int j = 0; j < verticalMatches.at(i).size(); j++) {
				cout << verticalMatches.at(i).at(j).get_color() << ' ';
			}
			cout << endl;
			cout << verticalCombs.at(i) << endl;
		}*/

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
		/*cout << "\nhorizontal:" << endl;
		for (int i = 0; i < horizontalCombs.size(); i++) {
			for (int j = 0; j < horizontalMatches.at(i).size(); j++) {
				cout << horizontalMatches.at(i).at(j).get_color() << ' ';
			}
			cout << endl;
			cout << horizontalCombs.at(i) << endl;
		}*/

		if (horizontalMatches.size() == 0 && verticalMatches.size() == 0) return;//there`s no combinations on the field

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

		/*cout << "vertical: " << endl;
		for (int i = 0; i < verticalCombs.size(); i++) {
			for (int j = 0; j < verticalMatches.at(i).size(); j++) {
				cout << verticalMatches.at(i).at(j).get_color() << ' ';
			}
			cout << endl;
			cout << verticalCombs.at(i) << endl;
		}

		cout << "\nhorizontal:" << endl;
		for (int i = 0; i < horizontalCombs.size(); i++) {
			for (int j = 0; j < horizontalMatches.at(i).size(); j++) {
				cout << horizontalMatches.at(i).at(j).get_color() << ' ';
			}
			cout << endl;
			cout << horizontalCombs.at(i) << endl;
		}

		cout << "\nspecial:" << endl;
		for (int i = 0; i < specialCombs.size(); i++) {
			for (int j = 0; j < specialMatches.at(i).size(); j++) {
				cout << specialMatches.at(i).at(j).get_color() << ' ';
			}
			cout << endl;
			cout << specialCombs.at(i) << endl;
		}*/
		//удаление кнопок
		thread hdelete([&] {
			if (horizontalMatches.size() > 0) {
				for (int i = 0; i < horizontalMatches.size(); i++)
				{
					for (int j = 0; j < horizontalMatches.at(i).size(); j++)
					{


						deleteButton(horizontalMatches.at(i).at(j).get_id());
					}
				}
			}
			});
		hdelete.join();

		thread vdelete([&] {
			if (verticalMatches.size() > 0) {
				for (int i = 0; i < verticalMatches.size(); i++)
				{
					for (int j = 0; j < verticalMatches.at(i).size(); j++)
					{
						deleteButton(verticalMatches.at(i).at(j).get_id());
					}
				}
			}
			});
		vdelete.join();

		thread sdelete([&] {
			if (specialMatches.size() > 0) {
				for (int i = 0; i < specialMatches.size(); i++)
				{
					for (int j = 0; j < specialMatches.at(i).size(); j++)
					{
						deleteButton(specialMatches.at(i).at(j).get_id());
					}
				}
			}
			});
		sdelete.join();

		//thread gap([&] {gapFill(); });
		//gap.join();
		gapFill();
		cout << "gapFill ended!" << endl;
		Clean();
		//return true;
	}

	void gapFill() {

		thread* th = new thread[width];
		//vector<vector<Button>> verticalMatches;
		for (int i = 0; i < width; i++)
		{
			this_thread::sleep_for(chrono::milliseconds(50));
			th[i] = thread([&] {
				int i1 = i;
			cout << "thread " << i1 << " started" << endl;
			srand(time(0) - width + (time_t)i1);
			bool finish = false;
			int tempColor;
			if (button[0][i1].get_color() == 6) button[0][i1].set("color", random(0, 5));
			while (!finish) {
				finish = true;
				for (int j = height - 1; j > 0; j--) {
					if (finish && button[j][i1].get_color() == 6) finish = false;
					if (!finish) {//move one tile down
						button[j][i1].set("color", button[j - 1][i1].get_color());
						button[j - 1][i1].set("color", 6);//black
					}
					cout << "column " << i1 << " moved" << endl;
					this_thread::sleep_for(chrono::milliseconds(250));
				}
				if (!finish) button[0][i1].set("color", random(0, 5));
			}
				});
			cout << "thread " << i << " ended" << endl;
			th[i].detach();
			this_thread::sleep_for(chrono::milliseconds(50));
		}



	}

	void buttonPress(int x, int y)
	{
		if (pressed++ == 0)
		{
			button[x][y].press("target");
			press[0] = x;
			press[1] = y;
		}
		else
		{
			button[x][y].press("target");
			button[x][y].swap(button[press[0]][press[1]]);
			button[x][y].press("untarget");
			button[press[0]][press[1]].press("untarget");
			pressed = 0;
			Clean();
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

	int size = min((100 / (int)pow(2, fieldWidth / 13) + 2), (100 / (int)pow(2, fieldHeight / 7) + 2));
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
				//cout << mousePos.y / 100 << " " << mousePos.x / 100 << endl;
				field.buttonPress(mousePos.y / 50, mousePos.x / 50);
			}
		}

		window.clear();

		for (int i = 0; i < fieldWidth; i++) for (int j = 0; j < fieldHeight; j++)
			window.draw(field.show(j, i));

		window.display();
	}
}