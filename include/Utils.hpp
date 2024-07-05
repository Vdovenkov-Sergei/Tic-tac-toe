#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define WINDOW_SIZE_X (800)
#define WINDOW_SIZE_Y (800)
#define SHIFT (25)
#define WIN_CASES (8)
#define SQUARE_SIZE (250)
#define SIGN_SIZE (200)
#define FIELD_SIZE (3)
#define TOTAL_VOLUME (10)

using namespace sf;
using namespace std;
using Triple = tuple<int, int, int>;

enum CEIL { EMPTY, CROSS, ZERO };
enum RESULT { WIN_ZERO, WIN_CROSS, DRAW };
enum STATES { GAME, FINISH };
enum WIN_CASE { G1, G2, G3, V1, V2, V3, DM, DS };

pair<int, int> findSquare(const vector<vector<enum CEIL>> &field, const Vector2i &mousePos);
pair<int, int> checkWinner(const vector<vector<enum CEIL>> &field, const int whoseStep, int &flag, const int free);
void drawWinnerLine(int caseWin, RenderWindow& window, RectangleShape& winLine);

#endif