#include "Field.h"
#include "Text.h"

Texts::Texts(int x, int y, int color, int size)
{
	if (!font.loadFromFile("fonts/LucidaTypewriterBold.ttf"))
		cout << "Error load font\n";

	text.setFont(font);
	text.setPosition(x, y);
	text.setFillColor(Color(Colors[color][0], Colors[color][1], Colors[color][2]));
	text.setCharacterSize(size);
}