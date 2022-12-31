#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Field.h"
#include "Button.h"
#include <iostream>
#include <windows.h>
#include <thread>
#include <ctime>
#include <chrono>
#include <mutex>
#include <future>
using namespace std;
using namespace sf;

Field::Field(int width, int height, int move, int score) : width(width), height(height), moves(move), score(score)
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

void Field::sleep(string type, int time)
{
	if (type == "ms") this_thread::sleep_for(chrono::milliseconds(time));
	else if (type == "sec") this_thread::sleep_for(chrono::seconds(time));
}

int Field::Clean() {
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
	for (int i = 0; i < horizontalMatches.size(); i++) {
		for (int j = 0; j < horizontalMatches.at(i).size(); j++) {
			for (int i1 = 0; i1 < verticalMatches.size(); i1++) {
				for (int j1 = 0; j1 < verticalMatches.at(i1).size(); j1++)
				{
					if (horizontalMatches.at(i).at(j).get_id() == verticalMatches.at(i1).at(j1).get_id()) {//if 2 combs share the same button
						specialMatches.push_back(horizontalMatches.at(i));
						for (int k = 0; k < verticalMatches.at(i1).size(); k++) {
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

	int point = 0;

	for (int i = 0; i < verticalMatches.size(); i++) point += verticalMatches.at(i).size();
	for (int i = 0; i < horizontalMatches.size(); i++) point += horizontalMatches.at(i).size();
	for (int i = 0; i < specialMatches.size(); i++) point += specialMatches.at(i).size()*2;

	return point;
}

void Field::gapFill() 
{
	future<void>* th = new future<void>[width]; //cout << this_thread::get_id() << endl;

	for (int i = 0; i < width; i++)
	{
		//sleep("ms", 1);
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

int Field::buttonPress(int x, int y)
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
			thread th1(&Field::beep, this, 500, 100); thread th2(&Field::beep, this, 300, 100);
			th1.detach(); th2.detach();
		}
		else // else if have combintions
		{
			player_point += clean;
			thread th1(&Field::beep, this, 750, 100); thread th2(&Field::beep, this, 800, 100);
			th1.detach(); th2.detach();
			moves--;

			
		}

		system("cls");
		cout << "CLEAN\t" << clean << endl;
		cout << "PLAYER POINT\t" << player_point << "\tNEED\t" << score << "\n";
		cout << "MOVES\t" << moves << "\n";

		if (player_point >= score) {
			cout << "123\n";
			cout << "YOU WIN!\n";
			beep(500, 250);
			beep(750, 250);
			beep(1000, 1000);
			return 1;
		}

		else if (moves == 0) {
			cout << "YOU LOSE!\n";
			beep(1000, 250);
			beep(750, 250);
			beep(500, 1000);
			return 1;
		}		
	}

	return 0;
}