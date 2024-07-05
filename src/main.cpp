#include "Utils.hpp"

int main() {

    RenderWindow window(VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "TIC-TAC-TOE");
    RectangleShape cross; Texture crossTexture;
    crossTexture.loadFromFile("resources/cross.png"); cross.setTexture(&crossTexture);
    cross.setSize(Vector2f(SIGN_SIZE, SIGN_SIZE));
    cross.setOrigin(cross.getSize().x / 2.0f, cross.getSize().y / 2.0f);
    RectangleShape zero; Texture zeroTexture;
    zeroTexture.loadFromFile("resources/zero.png"); zero.setTexture(&zeroTexture);
    zero.setSize(Vector2f(SIGN_SIZE, SIGN_SIZE));
    zero.setOrigin(zero.getSize().x / 2.0f, zero.getSize().y / 2.0f);
    RectangleShape backGround; Texture backGroundTexture;
    backGroundTexture.loadFromFile("resources/backGround.png"); backGround.setTexture(&backGroundTexture);
    backGround.setSize(Vector2f(WINDOW_SIZE_X - 2 * SHIFT, WINDOW_SIZE_Y - 2 * SHIFT));
    backGround.setPosition(Vector2f(SHIFT, SHIFT));
    RectangleShape winLine; Texture winLineTexture;
    winLineTexture.loadFromFile("resources/winLine.png");
    winLine.setTexture(&winLineTexture);

    // SoundBuffer finalCrossZero; Sound winCrossZero(finalCrossZero);
    // SoundBuffer finalDraw; Sound drawCrossZero(finalDraw);
    // Music mainMusic;
    // mainMusic.openFromFile("resources/mainMusic.ogg");
    // mainMusic.setLoop(true); mainMusic.setVolume(TOTAL_VOLUME / 2);

    // winCrossZero.setVolume(TOTAL_VOLUME);
    // drawCrossZero.setVolume(TOTAL_VOLUME);
    // finalCrossZero.loadFromFile("resources/winning.ogg");
    // finalDraw.loadFromFile("resources/draw.ogg");

    vector<vector<enum CEIL>> field(FIELD_SIZE, vector<enum CEIL>(FIELD_SIZE));
    int whoseStep = ZERO, flagGame = STATES::GAME;
    int x = -1, y = -1, result = -1, caseWin = -1, freeSquares = FIELD_SIZE * FIELD_SIZE;
    bool isActive = true;

    // mainMusic.play();
    while (window.isOpen())
    {
        Vector2i mousePos = Mouse::getPosition(window);
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) if (event.key.code == Keyboard::Escape) window.close();
            if (event.type == Event::Closed) window.close();

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left && flagGame == GAME && isActive) {
                    auto pos = findSquare(field, mousePos);
                    x = pos.first; y = pos.second;
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                if (x != -1 && y != -1 && event.mouseButton.button == Mouse::Left && flagGame == GAME && isActive) {
                    field[x][y] = (whoseStep == ZERO) ? ZERO : CROSS; freeSquares--;
                    auto check = checkWinner(field, whoseStep, flagGame, freeSquares);
                    result = check.first; caseWin = check.second;

                    if (whoseStep == ZERO) whoseStep = CROSS;
                    else whoseStep = ZERO;
                }
            }
        }

        window.clear(Color::Black);

        isActive = true;
        window.draw(backGround);
        for (int i = 0; i < FIELD_SIZE; ++i) {
            for (int j = 0; j < FIELD_SIZE; ++j) {
                if (field[i][j] == CEIL::CROSS) {
                    cross.setPosition(Vector2f((j + 0.5f) * SQUARE_SIZE + SHIFT, (i + 0.5f) * SQUARE_SIZE + SHIFT));
                    window.draw(cross);                       
                }
                else if (field[i][j] == CEIL::ZERO) {
                    zero.setPosition(Vector2f((j + 0.5f) * SQUARE_SIZE + SHIFT, (i + 0.5f) * SQUARE_SIZE + SHIFT));
                    window.draw(zero);
                }
            }
        }
        if (caseWin != -1) drawWinnerLine(caseWin, window, winLine);
        window.display();

        if (flagGame == FINISH) {
            // switch (result) {
            // case WIN_CROSS: case WIN_ZERO: winCrossZero.play(); break;
            // case DRAW: drawCrossZero.play(); break;
            // }
            
            sleep(milliseconds(5000));
            isActive = false; whoseStep = ZERO;
            freeSquares = FIELD_SIZE * FIELD_SIZE;
            result = -1; caseWin = -1; x = -1; y = -1;
            for (int i = 0; i < FIELD_SIZE; ++i) {
                for (int j = 0; j < FIELD_SIZE; ++j) {
                    field[i][j] = CEIL::EMPTY;
                }
            }
            flagGame = GAME;
        }
    }
    return 0;
}