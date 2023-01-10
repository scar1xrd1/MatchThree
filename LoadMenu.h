#include <SFML/Graphics.hpp>
#include "Objects.h"

void LoadMenu(RenderWindow& window) {

#pragma region SET PARAMETRS AND WINDOWS DRAW OBJECT
	string line;

	ifstream in("data/level.txt"); 
	if (in.is_open()) {
		while (getline(in, line)) {
			lvl_num = line;
			n = stoi(lvl_num);
		}
	}

	window.clear(Color(77, 58, 90));

	font.loadFromFile("fonts/LucidaTypewriterBold.ttf");

	play.setFont(font);
	play.setString("Play");
	play.setCharacterSize(55);
	play.setFillColor(Color(255, 255, 255));

	exit_t.setFont(font);
	exit_t.setString("Exit");
	exit_t.setCharacterSize(55);
	exit_t.setFillColor(Color(255, 255, 255));

	level_t.setFont(font);
	level_t.setString("Levels");
	level_t.setCharacterSize(55);
	level_t.setFillColor(Color(255, 255, 255));

	levels.setFont(font);
	levels.setString("Level");
	levels.setCharacterSize(55);
	levels.setFillColor(Color(255, 255, 255));

	num.setFont(font);
	num.setString(lvl_num);
	num.setCharacterSize(55);
	num.setFillColor(Color(255, 255, 255));


	note.setFont(font);
	note.setString("Press ESC to return to menu");
	note.setCharacterSize(25);
	note.setFillColor(Color(255, 255, 255));

	left_t.setFont(font);
	left_t.setString("<-");
	left_t.setCharacterSize(55);
	left_t.setFillColor(Color(255, 255, 255));

	right_t.setFont(font);
	right_t.setString("->");
	right_t.setCharacterSize(55);
	right_t.setFillColor(Color(255, 255, 255));

	start.setFont(font);
	start.setString("Start");
	start.setCharacterSize(55);
	start.setFillColor(Color(255, 255, 255));

	//------------------------------------------------------------

	rectangle.setFillColor(Color(197, 197, 197));

	Play_Btn.setFillColor(Color(197, 197, 197));
	Play_Btn.setOutlineThickness(10.f);
	Play_Btn.setOutlineColor(Color(240, 239, 243));

	Lvl_Btn.setFillColor(Color(197, 197, 197));
	Lvl_Btn.setOutlineThickness(10.f);
	Lvl_Btn.setOutlineColor(Color(240, 239, 243));

	Exit_Btn.setFillColor(Color(197, 197, 197));
	Exit_Btn.setOutlineThickness(10.f);
	Exit_Btn.setOutlineColor(Color(240, 239, 243));

	Left_Btn.setFillColor(Color(197, 197, 197));
	Left_Btn.setOutlineThickness(10.f);
	Left_Btn.setOutlineColor(Color(240, 239, 243));

	Right_Btn.setFillColor(Color(197, 197, 197));
	Right_Btn.setOutlineThickness(10.f);
	Right_Btn.setOutlineColor(Color(240, 239, 243));

	Start_Btn.setFillColor(Color(197, 197, 197));
	Start_Btn.setOutlineThickness(10.f);
	Start_Btn.setOutlineColor(Color(240, 239, 243));

	//------------------------------------------------------------

	Play_Btn.move(160, 175);
	Lvl_Btn.move(160, 325);
	Exit_Btn.move(160, 475);

	play.move(229, 175);
	level_t.move(200, 325);
	exit_t.move(229, 475);

	levels.move(210, 175);
	num.move(270, 300);
	note.move(0, 570);

	Left_Btn.move(60, 300);
	Right_Btn.move(460, 300);
	Start_Btn.move(160, 425);

	left_t.move(60, 295);
	right_t.move(460, 295);
	start.move(215, 425);

	rectangle.move(0, 0);

	window.draw(rectangle);
	window.draw(Play_Btn);
	window.draw(Lvl_Btn);
	window.draw(Exit_Btn);
	window.draw(play);
	window.draw(level_t);
	window.draw(exit_t);
	window.display();

#pragma endregion 
}
