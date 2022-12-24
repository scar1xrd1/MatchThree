#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
using namespace sf;

class Button
{
    int x, y;
    int r, g, b;
    Music sound_pressed;
    RectangleShape btn;

public:
    Button() {}

    Button(int x, int y, int r, int g, int b) : x(x), y(y), r(r), g(g), b(b)
    {
        btn.setSize(Vector2f(100, 100));
        btn.setPosition(x, y);
        btn.setFillColor(Color(r, g, b));
    }

    void check(Vector2i mouseP)
    {
        if (btn.getGlobalBounds().contains(mouseP.x, mouseP.y))
        {
            srand(time(0));
            cout << "PRessed\n";
            
            btn.setFillColor(Color(1 + rand() % (255 - 1 + 1), 1 + rand() % (255 - 1 + 1), 1 + rand() % (255 - 1 + 1)));
            
            sound_pressed.openFromFile("sounds/mouse_click.wav");//загружаем файл  
            sound_pressed.play();
        }
    }

    RectangleShape show()
    {
        return btn;
    }

    Button & operator = (const Button& obj)
    {
        btn.setSize(Vector2f(100, 100));
        btn.setPosition(obj.x, obj.y);
        btn.setFillColor(Color(obj.r, obj.g, obj.b));
        return *this;
    }
};

int main()
{
    RenderWindow window(VideoMode(600, 600), "Hello");
    window.setVerticalSyncEnabled(true);
    srand(time(0));

    int pos1 = 0;
    int pos2 = 0;
    int stop = 0;

    int focus = 0;

    int focus_x1 = 0;
    int focus_x2 = 0;
    int focus_y1 = 0;
    int focus_y2 = 0;

    Button button[6][6];

    int posX = 0;
    int posY;
    for (int i = 0; i < 6; i++)
    {
        posY = 0;
        for (int j = 0; j < 6; j++)
        {
            button[i][j] = Button(posX, posY, 1 + rand() % (500 - 1 + 1), 1 + rand() % (500 - 1 + 1), 1 + rand() % (500 - 1 + 1));
            posY += 100;
        }  
        posX += 100;
    }

    while (window.isOpen())
    {
        Vector2i mousePos = Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        button[i][j].check(mousePos);
                    }                    
                }                
            }
        }

        window.clear();
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                window.draw(button[i][j].show());
            }
            
        }
        window.display();
    }

    return 0;
}