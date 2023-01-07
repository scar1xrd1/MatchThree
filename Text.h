#pragma once
#include "Field.h"

class Texts
{
	int Colors[1][3]{ {255, 255, 255} };
	Font font;
	Text text;

public:
	Texts(int, int, int, int);

	Text show() { return text; }

	void set(string t) { text.setString(t); }
};