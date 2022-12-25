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
    int row, column;
    Music sound_pressed;
    RectangleShape btn;


public:
    Button() {}

    Button(int x, int y, int row, int column, int r, int g, int b) : x(x), y(y), row(row), column(column), r(r), g(g), b(b)
    {
        btn.setSize(Vector2f(100, 100));
        btn.setPosition(x, y);
        btn.setFillColor(Color(r, g, b));
        
    }

    void target() {
        btn.setFillColor(Color(btn.getFillColor().r + 25, btn.getFillColor().g + 25, btn.getFillColor().b + 25));
        cout << "target" << endl;
    }

    void untarget() {
        btn.setFillColor(Color(btn.getFillColor().r - 25, btn.getFillColor().g - 25, btn.getFillColor().b - 25));
    }

    void press()
    {
        //srand(time(0));
        cout << "PRessed\n";
        target();
        sound_pressed.openFromFile("sounds/mouse_click.wav");//çàãðóæàåì ôàéë  
        sound_pressed.play();
        
    }

    void press(Button& btn1)
    {
        //srand(time(0));
        cout << "PRessed 2nd\n";
        //target();
        //btn.setFillColor(Color(btn.getFillColor().r - 25, btn.getFillColor().g - 25, btn.getFillColor().b - 25));
        sound_pressed.openFromFile("sounds/mouse_click.wav");//çàãðóæàåì ôàéë  
        sound_pressed.play();
        this_thread::sleep_for(chrono::milliseconds(1000));
        //untarget();
        //btn.setFillColor(Color(btn.getFillColor().r + 25, btn.getFillColor().g + 25, btn.getFillColor().b + 25));
        btn1.untarget();
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

class Field {
private:
    Button** button;
    int width, height;
    int colors[6][3]{ {101, 83, 172}, {188, 76, 67}, {67, 188, 76}, {67, 188, 76}, {194, 193, 61}, {61, 194, 193} };
    bool pressed;
    int pressedButton[2];
public:

    Field(int w, int h) : width(w), height(h) {
        pressed = false;
        button = new Button * [height];
        for (int i = 0; i < height; i++)//buttons array creation
        {
            button[i] = new Button[width];
        }

        int posX = 0;
        int posY;
        for (int i = 0; i < width; i++)//buttons array filling
        {
            posY = 0;
            for (int j = 0; j < height; j++)
            {
                int r = rand() % (5 + 1);
                button[j][i] = Button(posX, posY, j, i, colors[r][0], colors[r][1], colors[r][2]);
                posY += 100;
            }
            posX += 100;
        }
    }

    void ButtonPress(int i, int j) {
        if (!pressed) {
            button[i][j].press();
            pressedButton[0] = i;
            pressedButton[1] = j;
        }
        else {
            button[i][j].press(button[pressedButton[0]][pressedButton[1]]);
        }
        pressed = !pressed;
    }

    Button& getButton(int i, int j) {
        return button[i][j];
    }
};

int main()
{
    RenderWindow window(VideoMode(600, 600), "Hello");
    window.setVerticalSyncEnabled(true);
    srand(time(0));

    

    Field field(6, 6);
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
                cout << mousePos.x / 100 << mousePos.y / 100;
                //button[mousePos.y / 100][mousePos.x / 100].press();
                field.ButtonPress(mousePos.y / 100, mousePos.x / 100);
            }
        }

        window.clear();
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                window.draw(field.getButton(i, j).show());
            }
            
        }
        window.display();
    }

    return 0;
}