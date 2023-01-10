#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <string> 
using namespace std;
#include "Objects.h";

void LoadMenu(RenderWindow& window) {

#pragma region SET PARAMETRS AND WINDOWS DRAW OBJECT

	window.clear(Color(77, 58, 90));

	font.loadFromFile("LucidaTypewriterBold.ttf");

	name.setFont(font);
	name.setString("Match-three game");
	name.setCharacterSize(50);
	name.setFillColor(Color(255, 255, 255));

	select.setFont(font);
	select.setString("Select Level");
	select.setCharacterSize(50);
	select.setFillColor(Color(255, 255, 255));

	play.setFont(font);
	play.setString("Play");
	play.setCharacterSize(50);
	play.setFillColor(Color(255, 255, 255));

	exit_t.setFont(font);
	exit_t.setString("Exit");
	exit_t.setCharacterSize(50);
	exit_t.setFillColor(Color(255, 255, 255));

	level_t.setFont(font);
	level_t.setString("Levels");
	level_t.setCharacterSize(50);
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
	left_t.setCharacterSize(50);
	left_t.setFillColor(Color(255, 255, 255));

	right_t.setFont(font);
	right_t.setString("->");
	right_t.setCharacterSize(50);
	right_t.setFillColor(Color(255, 255, 255));

	start.setFont(font);
	start.setString("Start");
	start.setCharacterSize(50);
	start.setFillColor(Color(255, 255, 255));

	//------------------------------------------------------------

	rectangle.setFillColor(Color(197, 197, 197));

	Play_Btn.setFillColor(Color(197, 197, 197));
	Play_Btn.setOutlineThickness(7.f);
	Play_Btn.setOutlineColor(Color(240, 239, 243));

	Lvl_Btn.setFillColor(Color(197, 197, 197));
	Lvl_Btn.setOutlineThickness(7.f);
	Lvl_Btn.setOutlineColor(Color(240, 239, 243));

	Exit_Btn.setFillColor(Color(197, 197, 197));
	Exit_Btn.setOutlineThickness(7.f);
	Exit_Btn.setOutlineColor(Color(240, 239, 243));

	Left_Btn.setFillColor(Color(197, 197, 197));
	Left_Btn.setOutlineThickness(7.f);
	Left_Btn.setOutlineColor(Color(240, 239, 243));

	Right_Btn.setFillColor(Color(197, 197, 197));
	Right_Btn.setOutlineThickness(7.f);
	Right_Btn.setOutlineColor(Color(240, 239, 243));

	Start_Btn.setFillColor(Color(197, 197, 197));
	Start_Btn.setOutlineThickness(7.f);
	Start_Btn.setOutlineColor(Color(240, 239, 243));

	//------------------------------------------------------------

	Play_Btn.move(160, 174);
	Lvl_Btn.move(160, 324);
	Exit_Btn.move(160, 474);

	name.move(60, 0);
	select.move(130, 0);
	play.move(234, 175);
	level_t.move(205, 325);
	exit_t.move(234, 475);

	levels.move(210, 175);
	num.move(270, 300);
	note.move(0, 570);

	Left_Btn.move(60, 300);
	Right_Btn.move(460, 300);
	Start_Btn.move(160, 425);

	left_t.move(61, 297);
	right_t.move(461, 297);
	start.move(216, 426);

	rectangle.move(0, 0);

	window.draw(rectangle);
	window.draw(Play_Btn);
	window.draw(Lvl_Btn);
	window.draw(Exit_Btn);
	window.draw(name);
	window.draw(play);
	window.draw(level_t);
	window.draw(exit_t);
	window.display();

#pragma endregion 

}
