#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <string> 
using namespace std;
#include "Objects.h";

class NavMenu {

public:
	void navigation(RenderWindow& window) {

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

		//���� ������ ������ PLAY � ��� �������
		if (Play_Btn.getGlobalBounds().contains(pos.x, pos.y) && Play_Btn.getFillColor() != Color::Transparent) {
			//...��� ��� ������� ���� � ������� 1
			window.close();
			cout << "game started";
		}

		//���� ������ ������ EXIT � ��� �������
		if (Exit_Btn.getGlobalBounds().contains(pos.x, pos.y) && Exit_Btn.getFillColor() != Color::Transparent) {
			window.close();
			cout << "exit";
		}

		//���� ������ ������ LEVELS
		if (Lvl_Btn.getGlobalBounds().contains(pos.x, pos.y) && Lvl_Btn.getFillColor() != Color::Transparent) {

			//������� ���������� ��� ��� ������ ��������
			name.setFillColor(Color::Transparent);
			Play_Btn.setFillColor(Color::Transparent);
			Play_Btn.setOutlineColor(Color::Transparent);
			play.setFillColor(Color::Transparent);
			Exit_Btn.setFillColor(Color::Transparent);
			Exit_Btn.setOutlineColor(Color::Transparent);
			exit_t.setFillColor(Color::Transparent);
			Lvl_Btn.setFillColor(Color::Transparent);
			Lvl_Btn.setOutlineColor(Color::Transparent);
			level_t.setFillColor(Color::Transparent);

			//���������� ����� ��������		
			window.clear(Color(77, 58, 90));
			window.draw(rectangle);
			window.draw(select);
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

		// ������ - LEFT
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

			window.clear(Color(77, 58, 90));
			window.draw(rectangle);
			window.draw(select);
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

		//������ - RIGHT
		if (Right_Btn.getGlobalBounds().contains(pos.x, pos.y) && Right_Btn.getFillColor() != Color::Transparent) {

			n = n + 1;
			lvl_num = to_string(n);
			num.setString(lvl_num);

			window.clear(Color(77, 58, 90));
			window.draw(rectangle);
			window.draw(select);
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

		//���� ������ ������ PLAY � ��� �������
		if (Start_Btn.getGlobalBounds().contains(pos.x, pos.y) && Start_Btn.getFillColor() != Color::Transparent) {

			//...��� ��� ������� ���� � ������� n
			/*void SelectLevel(int n) {

			}*/
			cout << "Level selected";
		}

	}
};
