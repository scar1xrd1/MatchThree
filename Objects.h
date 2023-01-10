#ifndef OBJECTS
#define OBJECTS
#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <string> 
using namespace std;

Font font;

Text play; Text exit_t; Text level_t;
Text levels; Text num; Text note;
Text left_t; Text right_t; Text start;
Text name; Text select;

RectangleShape rectangle(Vector2f(600, 84));
RectangleShape Play_Btn(Vector2f(270, 70));
RectangleShape Lvl_Btn(Vector2f(270, 70));
RectangleShape Exit_Btn(Vector2f(270, 70));
RectangleShape Left_Btn(Vector2f(70, 70));
RectangleShape Right_Btn(Vector2f(70, 70));
RectangleShape Start_Btn(Vector2f(270, 70));

int n = 1;
string lvl_num = to_string(n);
Vector2i pos;

#endif