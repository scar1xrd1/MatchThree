#include "Button.h"

Button::Button(int x, int y, int color, int id, int size) : current_color(color), x(x), y(y), id(id)
{
	btn.setSize(Vector2f(size, size));
	btn.setFillColor(Color(iColor[color][0], iColor[color][1], iColor[color][2]));
	btn.setPosition(x, y);
}

void Button::press(string value) { if (!pressed) set(value, 0); }

void Button::swap(Button& other)
{
	int a = current_color;
	set("color", other.get_color());
	other.set("color", a);
}

void Button::changeState(int state) {

}

void Button::set(string data, int value1)
{
	if (data == "color")
	{
		current_color = value1;
		btn.setFillColor(Color(iColor[value1][0], iColor[value1][1], iColor[value1][2]));
	}
	else if (data == "target") btn.setFillColor(Color(iColor[current_color][0] + 25, iColor[current_color][1] + 25, iColor[current_color][2] + 25));
	else if (data == "untarget") btn.setFillColor(Color(iColor[current_color][0], iColor[current_color][1], iColor[current_color][2]));
}

void Button::set(string data, int value1, int value2)
{
	if (data == "xy")
	{
		x = value1; y = value2;
		btn.setPosition(x, y);
	}
}

int Button::get_xy(string value)
{
	if (value == "x") return x;
	if (value == "y") return y;
}