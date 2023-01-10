#include <SFML/Graphics.hpp>
#include "Objects.h"

class NavMenu
{
public:
	void beep(int freq, int m) { Beep(freq, m); }

	int navigation(RenderWindow& window) {

		pos = Mouse::getPosition(window);

		levels.setFillColor(Color(255, 255, 255));
		num.setFillColor(Color(255, 255, 255));
		note.setFillColor(Color(255, 255, 255));
		left_t.setFillColor(Color(255, 255, 255));
		right_t.setFillColor(Color(255, 255, 255));
		start.setFillColor(Color(255, 255, 255));

		Left_Btn.setFillColor(Color(197, 197, 197));
		Left_Btn.setOutlineColor(Color(240, 239, 243));

		Right_Btn.setFillColor(Color(197, 197, 197));
		Right_Btn.setOutlineColor(Color(240, 239, 243));

		Start_Btn.setFillColor(Color(197, 197, 197));
		Start_Btn.setOutlineColor(Color(240, 239, 243));

		//ĹŃËČ ÍŔĆŔŇŔ ĘÍÎĎĘŔ PLAY č îíŕ ŕęňčâíŕ
		if (Play_Btn.getGlobalBounds().contains(pos.x, pos.y) && Play_Btn.getFillColor() != Color::Transparent) {
			beep(600, 75);
			//...ŇÓŇ ĘÎÄ ÇŔĎÓŃĘŔ ČĂĐŰ Ń ÓĐÎÂÍĹĚ 1
			window.close();
			cout << "game started";
		}

		//ĹŃËČ íŕćŕňŕ ęíîďęŕ EXIT č îíŕ ŕęňčâíŕ
		if (Exit_Btn.getGlobalBounds().contains(pos.x, pos.y) && Exit_Btn.getFillColor() != Color::Transparent) {
			beep(600, 75);
			window.close();
			cout << "exit";
			return -1;
		}

		//ĹŃËČ íŕćŕňŕ ęíîďęŕ LEVELS
		if (Lvl_Btn.getGlobalBounds().contains(pos.x, pos.y) && Lvl_Btn.getFillColor() != Color::Transparent) {
			beep(600, 75);
			//Ńîçäŕĺě ďđîçđŕ÷íűé ôîí äë˙ ŃŇŔĐŰŐ îáüĺęňîâ
			Play_Btn.setFillColor(Color::Transparent);
			Play_Btn.setOutlineColor(Color::Transparent);
			play.setFillColor(Color::Transparent);
			Exit_Btn.setFillColor(Color::Transparent);
			Exit_Btn.setOutlineColor(Color::Transparent);
			exit_t.setFillColor(Color::Transparent);
			Lvl_Btn.setFillColor(Color::Transparent);
			Lvl_Btn.setOutlineColor(Color::Transparent);
			level_t.setFillColor(Color::Transparent);

			//ďđîđčńîâęŕ ÍÎÂŰŐ îáüĺęňîâ		
			window.clear(Color(77, 58, 90));
			window.draw(Start_Btn);
			window.draw(Left_Btn);
			window.draw(Right_Btn);
			window.draw(levels);
			window.draw(num);
			window.draw(note);
			window.draw(left_t);
			window.draw(right_t);
			window.draw(start);
			window.display();

		}

		// ĘÍÎĎĘŔ - LEFT
		if (Left_Btn.getGlobalBounds().contains(pos.x, pos.y) && Left_Btn.getFillColor() != Color::Transparent) {

			if ((n - 1) <= 0) {
				n = 1;
				lvl_num = to_string(n);
				num.setString(lvl_num);
			}
			else {
				n = n - 1;
				lvl_num = to_string(n);
				num.setString(lvl_num);
			}

			beep(600, 75);

			ofstream f("data/level.txt");
			f << lvl_num;
			f.close();

			window.clear(Color(77, 58, 90));
			window.draw(Start_Btn);
			window.draw(Left_Btn);
			window.draw(Right_Btn);
			window.draw(levels);
			window.draw(num);
			window.draw(note);
			window.draw(left_t);
			window.draw(right_t);
			window.draw(start);
			window.display();
		}

		//ĘÍÎĎĘŔ - RIGHT
		if (Right_Btn.getGlobalBounds().contains(pos.x, pos.y) && Right_Btn.getFillColor() != Color::Transparent) {
			beep(600, 75);

			if(n+1 != 11) n = n + 1;
			lvl_num = to_string(n);
			num.setString(lvl_num);

			ofstream f("data/level.txt");
			f << lvl_num;
			f.close();

			window.clear(Color(77, 58, 90));
			window.draw(Start_Btn);
			window.draw(Left_Btn);
			window.draw(Right_Btn);
			window.draw(levels);
			window.draw(num);
			window.draw(note);
			window.draw(left_t);
			window.draw(right_t);
			window.draw(start);
			window.display();
		}

		//ĹŃËČ ÍŔĆŔŇŔ ĘÍÎĎĘŔ PLAY č îíŕ ŕęňčâíŕ
		if (Start_Btn.getGlobalBounds().contains(pos.x, pos.y) && Start_Btn.getFillColor() != Color::Transparent) {
			//...ŇÓŇ ĘÎÄ ÇŔĎÓŃĘŔ ČĂĐŰ Ń ÓĐÎÂÍĹĚ n
			/*void SelectLevel(int n) {

			}*/
			cout << "Level selected";
			beep(600, 75);
			beep(750, 75);
		}
		return 0;
	}
};