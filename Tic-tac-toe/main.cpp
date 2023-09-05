#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Functions.h"
using namespace sf;

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(1200, 1100), "Tic-tac-toe");
    RectangleShape First(Vector2f(SIZE_SQUARE - OUTLINE * 2, SIZE_SQUARE - OUTLINE * 2));
    RectangleShape Second(Vector2f(SIZE_SQUARE - OUTLINE * 2, SIZE_SQUARE - OUTLINE * 2));
    RectangleShape Cross; Texture cross; cross.loadFromFile("CROSS.png"); Cross.setTexture(&cross);
    RectangleShape Zero; Texture zero; zero.loadFromFile("ZERO.png"); Zero.setTexture(&zero);
    RectangleShape True(Vector2f(50, 50)); Texture TRUE; TRUE.loadFromFile("+.png"); True.setTexture(&TRUE);
    True.setOutlineColor(Color::Black);
    True.setOutlineThickness(OUTLINE);
    RectangleShape False(Vector2f(50, 50)); Texture FALSE; FALSE.loadFromFile("-.png"); False.setTexture(&FALSE);
    False.setOutlineColor(Color::Black);
    False.setOutlineThickness(OUTLINE);
    RectangleShape Name(Vector2f(800, 150)); Texture NAME; NAME.loadFromFile("NAME.png"); Name.setTexture(&NAME);
    RectangleShape Menu(Vector2f(150, 500));
    Menu.setFillColor(Color(178, 126, 229));
    Menu.setOutlineColor(Color::Black);
    Menu.setOutlineThickness(OUTLINE);
    RectangleShape Star(Vector2f(80, 80)); Texture STAR; STAR.loadFromFile("STAR.png"); Star.setTexture(&STAR);
    Star.setOrigin(Star.getSize().x / 2.0, Star.getSize().y / 2.0);
    RectangleShape Butterfly(Vector2f(100, 100)); 
    Texture BUTTERFLY; BUTTERFLY.loadFromFile("BUTTERFLY.png"); Butterfly.setTexture(&BUTTERFLY);
    Butterfly.setOrigin(Butterfly.getSize().x / 2.0, Butterfly.getSize().y / 2.0);

    RectangleShape GV_Line(Vector2f(650, 10)); RectangleShape D_Line(Vector2f(920, 10));
    GV_Line.setFillColor(Color(227, 95, 95)); D_Line.setFillColor(Color(227, 95, 95));


    Texture first; first.loadFromFile("FIRST.jpg");
    Texture second; second.loadFromFile("SECOND.png");
    First.setTexture(&first); Second.setTexture(&second);
    First.setOutlineColor(Color::Black);
    First.setOutlineThickness(OUTLINE);
    Second.setOutlineColor(Color::Black);
    Second.setOutlineThickness(OUTLINE);

    ConvexShape Back;
    Back.setPointCount(6);
    Back.setPoint(0, Vector2f(0, 80));
    Back.setPoint(1, Vector2f(60, 0));
    Back.setPoint(2, Vector2f(840, 0));
    Back.setPoint(3, Vector2f(900, 80));
    Back.setPoint(4, Vector2f(840, 160));
    Back.setPoint(5, Vector2f(60, 160));
    Back.setFillColor(Color(178, 126, 229));
    Back.setOutlineColor(Color::Black);
    Back.setOutlineThickness(OUTLINE);

    SoundBuffer WINCROSS; Sound Wincross(WINCROSS);
    SoundBuffer WINZERO; Sound WinZero(WINZERO);
    SoundBuffer ONLYDRAW; Sound Draw(ONLYDRAW);
    Music MainMusic;    
    MainMusic.openFromFile("MAIN_MUSIC.ogg");
    MainMusic.setLoop(true); MainMusic.setVolume(10);

    Wincross.setVolume(40);
    WinZero.setVolume(40);
    Draw.setVolume(40);
    WINCROSS.loadFromFile("WIN_CROSS.ogg");
    WINZERO.loadFromFile("WIN_ZERO.ogg");
    ONLYDRAW.loadFromFile("DRAW.ogg");


    SQUARE field[SIZE][SIZE] = { 0 }; InitField(field);
    int WhoseMove = ZERO, y1 = NONE, y2 = NONE; float tick = 0, angle = 0, stop = false;
    int x = NONE, y = NONE, FLAG_GAME = GAME, result = NONE, free_sq = SIZE * SIZE, Case = NONE;
    int stars_x[COUNT] = { 80, 1120, 877, 1147, 877, 1147 };
    int stars_y[COUNT] = { 137, 137, 365, 365, 985, 985 };

    MainMusic.play();
    while (window.isOpen())
    {
        Vector2i mousePos = Mouse::getPosition(window);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed) if (event.key.code == Keyboard::Escape) window.close();
            if (event.type == Event::Closed) window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.key.code == Mouse::Left && FLAG_GAME == GAME && stop == false)
                {
                    FindSquare(field, mousePos.x, mousePos.y, &x, &y);
                }
            }
            if (event.type == Event::MouseButtonReleased)
            {
                if (event.key.code == Mouse::Left)
                {
                    if (x != NONE && y != NONE && FLAG_GAME == GAME && stop == false)
                    {
                        field[x][y].what = (WhoseMove == ZERO) ? ZERO : CROSS;
                        result = CheckSbWin(field, WhoseMove, &FLAG_GAME, &free_sq, &Case);
                        if (WhoseMove == ZERO) WhoseMove = CROSS; else WhoseMove = ZERO;
                    }
                }
            }
        }

        window.clear(Color(103, 235, 211));

        stop = false;
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if (field[i][j].color == FIRST)
                {
                    First.setPosition(Vector2f(j * (First.getSize().x + OUTLINE) + OUTLINE + SHIFT_1,
                                                i * (First.getSize().y + OUTLINE) + OUTLINE + SHIFT_2));
                    window.draw(First);
                }
                else if (field[i][j].color == SECOND)
                {
                    Second.setPosition(Vector2f(j * (Second.getSize().x + OUTLINE) + OUTLINE + SHIFT_1,
                                                i * (Second.getSize().y + OUTLINE) + OUTLINE + SHIFT_2));
                    window.draw(Second);
                }

                if (field[i][j].what == CROSS)
                {
                    Cross.setSize(Vector2f(130, 130));
                    Cross.setOrigin(Vector2f(Cross.getSize().x / 2.0, Cross.getSize().y / 2.0));
                    Cross.setPosition(Vector2f((j * 2 + 1) * 125 + SHIFT_1 - j * OUTLINE, (i * 2 + 1) * 125 + SHIFT_2 - i * OUTLINE));
                    window.draw(Cross);                       
                }
                else if (field[i][j].what == ZERO)
                {
                    Zero.setSize(Vector2f(130, 130));
                    Zero.setOrigin(Vector2f(Zero.getSize().x / 2.0, Zero.getSize().y / 2.0));
                    Zero.setPosition(Vector2f((j * 2 + 1) * 125 + SHIFT_1 - j * OUTLINE, (i * 2 + 1) * 125 + SHIFT_2 - i * OUTLINE));
                    window.draw(Zero);
                }
            }
        }
        if (true)
        {
            Back.setPosition(Vector2f(150, 57.5));
            window.draw(Back);
            Name.setPosition(Vector2f(200, 62.5));
            window.draw(Name);

            Menu.setPosition(Vector2f(SHIFT_1 + SIZE_SQUARE * 3 + 112.5, 425));
            window.draw(Menu);
            Cross.setSize(Vector2f(100, 100));
            Cross.setOrigin(Vector2f(Cross.getSize().x / 2.0, Cross.getSize().y / 2.0));
            Cross.setPosition(Vector2f(Menu.getPosition().x + 75, 490));
            window.draw(Cross);
            Zero.setSize(Vector2f(100, 100));
            Zero.setOrigin(Vector2f(Zero.getSize().x / 2.0, Zero.getSize().y / 2.0));
            Zero.setPosition(Vector2f(Menu.getPosition().x + 75, 860));
            window.draw(Zero);

            if (WhoseMove == CROSS) { y1 = 570; y2 = 730; }
            else if (WhoseMove == ZERO) { y1 = 730; y2 = 570; }
            True.setPosition(Vector2f(Menu.getPosition().x + 50, y1));
            window.draw(True);
            False.setPosition(Vector2f(Menu.getPosition().x + 50, y2));
            window.draw(False);

            for (int i = 0; i < COUNT; ++i)
            {
                Star.setRotation(tick);
                Star.setPosition(Vector2f(stars_x[i], stars_y[i]));
                window.draw(Star);
            }
            Butterfly.setPosition(Vector2f(1012, 340));
            window.draw(Butterfly);
            Butterfly.setPosition(Vector2f(1012, 1010));
            window.draw(Butterfly);
        }

        if (Case == G1 || Case == G2 || Case == G3)
        {
            angle = 0;
            GV_Line.setRotation(angle);
            GV_Line.setPosition(Vector2f(SHIFT_1 + 42, SHIFT_2 + 242 * Case + 120));
            window.draw(GV_Line);
        }
        else if (Case == V1 || Case == V2 || Case == V3)
        {
            angle = 90;
            GV_Line.setRotation(angle);
            GV_Line.setPosition(Vector2f(SHIFT_1 + 242 * (Case % SIZE) + 130, SHIFT_2 + 42));
            window.draw(GV_Line);
        }
        else if (Case == DM)
        {
            angle = 45;
            D_Line.setRotation(angle);
            D_Line.setPosition(Vector2f(SHIFT_1 + 50, SHIFT_2 + 42));
            window.draw(D_Line);
        }
        else if (Case == DS)
        {
            angle = -45;
            D_Line.setRotation(angle);
            D_Line.setPosition(Vector2f(SHIFT_1 + 42, SHIFT_2 + 685));
            window.draw(D_Line);
        }

        window.display();
        if (FLAG_GAME == FINISH)
        {
            switch (result)
            {
            case WIN_CROSS: Wincross.play(); break;
            case WIN_ZERO: WinZero.play(); break;
            case DRAW: Draw.play(); break;
            }
            sleep(milliseconds(4000));
            WhoseMove = ZERO; InitField(field);
            free_sq = SIZE * SIZE; result = NONE; Case = NONE;
            x = NONE; y = NONE;
            FLAG_GAME = GAME; stop = true;
        }
        tick += 0.2;
    }
    return 0;
}