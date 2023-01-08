#include <SFML/Graphics.hpp>
#include "Objects.h"

void RefreshMenu(RenderWindow& window) {
	rectangle.setFillColor(Color(197, 197, 197));

	Play_Btn.setFillColor(Color(197, 197, 197));
	Play_Btn.setOutlineColor(Color(240, 239, 243));

	Lvl_Btn.setFillColor(Color(197, 197, 197));
	Lvl_Btn.setOutlineColor(Color(240, 239, 243));

	Exit_Btn.setFillColor(Color(197, 197, 197));
	Exit_Btn.setOutlineColor(Color(240, 239, 243));

	play.setFillColor(Color(255, 255, 255));
	exit_t.setFillColor(Color(255, 255, 255));
	level_t.setFillColor(Color(255, 255, 255));

	Left_Btn.setFillColor(Color::Transparent);
	Left_Btn.setOutlineColor(Color::Transparent);

	Right_Btn.setFillColor(Color::Transparent);
	Right_Btn.setOutlineColor(Color::Transparent);

	Start_Btn.setFillColor(Color::Transparent);
	Start_Btn.setOutlineColor(Color::Transparent);


	levels.setFillColor(Color::Transparent);
	num.setFillColor(Color::Transparent);
	note.setFillColor(Color::Transparent);
	left_t.setFillColor(Color::Transparent);
	right_t.setFillColor(Color::Transparent);
	start.setFillColor(Color::Transparent);

	window.draw(rectangle);
	window.draw(Play_Btn);
	window.draw(Lvl_Btn);
	window.draw(Exit_Btn);
	window.draw(play);
	window.draw(level_t);
	window.draw(exit_t);
}