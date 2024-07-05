#include "Utils.hpp"

vector<Triple> posX = {{0, 0, 0}, {1, 1, 1}, 
					   {2, 2, 2}, {0, 1, 2}, 
					   {0, 1, 2}, {0, 1, 2}, 
					   {0, 1, 2}, {0, 1, 2}};

vector<Triple> posY = {{0, 1, 2}, {0, 1, 2}, 
					   {0, 1, 2}, {0, 0, 0}, 
					   {1, 1, 1}, {2, 2, 2}, 
					   {0, 1, 2}, {2, 1, 0}};

pair<int, int> findSquare(const vector<vector<enum CEIL>>& field, const Vector2i &mousePos) {
	pair<int, int> posSquare = {-1, -1};
	if (mousePos.x >= SHIFT && mousePos.x <= WINDOW_SIZE_X - SHIFT && 
		mousePos.y >= SHIFT && mousePos.y <= WINDOW_SIZE_Y - SHIFT) {
		posSquare.first = (mousePos.y - SHIFT) / SQUARE_SIZE;
		posSquare.second = (mousePos.x - SHIFT) / SQUARE_SIZE;
	}
	return posSquare;
}

pair<int, int> checkWinner(const vector<vector<enum CEIL>> &field, const int whoseStep, int& flag, const int free) {
	auto result = RESULT::DRAW; int caseWin = -1;

	for (int i = 0; i < WIN_CASES; ++i) {

		int x1, x2, x3, y1, y2, y3;
		std::tie(x1, x2, x3) = posX[i]; std::tie(y1, y2, y3) = posY[i];

		if (field[x1][y1] != CEIL::EMPTY && field[x1][y1] == field[x2][y2] && field[x2][y2] == field[x3][y3]) {
			flag = STATES::FINISH; caseWin = i;
			result = (whoseStep == CROSS) ? RESULT::WIN_CROSS : RESULT::WIN_ZERO;
			return {result, caseWin};
		}
	}

	if (!free) {
		flag = FINISH;
		return {result, caseWin};
	}
	return {-1, -1};
}

void drawWinnerLine(int caseWin, RenderWindow& window, RectangleShape& winLine)
{
	float angle = 0, posX = -1, posY = 1, sizeX = -1, sizeY = SHIFT;
	if (caseWin == G1 || caseWin == G2 || caseWin == G3) {
	    angle = 0;
		sizeX = WINDOW_SIZE_X - 2 * SHIFT;
		posX = SHIFT;
		posY = SHIFT + caseWin * SQUARE_SIZE + (SQUARE_SIZE - sizeY) / 2;
	}
	else if (caseWin == V1 || caseWin == V2 || caseWin == V3) {
	    angle = 90;
		sizeX = WINDOW_SIZE_X - 2 * SHIFT;
		posX = SHIFT + (caseWin - 3) * SQUARE_SIZE + (SQUARE_SIZE + sizeY) / 2;
		posY = SHIFT;
	}
	else if (caseWin == DM) {
	    angle = 45;
		sizeX = (WINDOW_SIZE_X - 2 * SHIFT) * sqrt(2);
		posX = SHIFT + (sizeY / 2.0f / sqrt(2));
		posY = SHIFT - (sizeY / 2.0f / sqrt(2));
	}
	else {
	    angle = -45;
		sizeX = (WINDOW_SIZE_X - 2 * SHIFT) * sqrt(2);
		posX = SHIFT - (sizeY / 2.0f / sqrt(2));
		posY = WINDOW_SIZE_Y - SHIFT - (sizeY / 2.0f / sqrt(2));
	}

	winLine.setSize(Vector2f(sizeX, sizeY));
	winLine.setRotation(angle);
	winLine.setPosition(Vector2f(posX, posY));
	window.draw(winLine);
}