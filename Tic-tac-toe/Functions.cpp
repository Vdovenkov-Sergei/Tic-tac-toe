#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Functions.h"

int dir_x[CASES][SIZE] = { {0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 1, 2} };
int dir_y[CASES][SIZE] = { {0, 1, 2}, {0, 1, 2}, {0, 1, 2}, {0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {0, 1, 2}, {2, 1, 0} };

void InitField(SQUARE field[][SIZE])
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			field[i][j].what = EMPTY;
			if (i % PARITY == false && j % PARITY == false || i % PARITY == true && j % PARITY == true)
			{
				field[i][j].color = FIRST;
			}
			else
			{
				field[i][j].color = SECOND;
			}
		}
	}
}
void FindSquare(SQUARE field[][SIZE], int mouseX, int mouseY, int* x, int* y)
{
	*x = NONE; *y = NONE;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (mouseX >= j * (SIZE_SQUARE - OUTLINE) + OUTLINE + SHIFT_1 &&
				mouseX <= j * (SIZE_SQUARE - OUTLINE) + SHIFT_1 + SIZE_SQUARE - OUTLINE &&
				mouseY >= i * (SIZE_SQUARE - OUTLINE) + OUTLINE + SHIFT_2 &&
				mouseY <= i * (SIZE_SQUARE - OUTLINE) + SHIFT_2 + SIZE_SQUARE - OUTLINE && field[i][j].what == EMPTY)
			{
				*x = i; *y = j;
			}
		}
	}
}
int CheckSbWin(SQUARE field[][SIZE], int step, int* flag, int* free_sq, int* Case)
{
	int result = NONE;
	if ((*free_sq)) (*free_sq)--;
	for (int i = 0; i < CASES; ++i)
	{
		int x1 = dir_x[i][FIRST], x2 = dir_x[i][SECOND], x3 = dir_x[i][THIRD];
		int y1 = dir_y[i][FIRST], y2 = dir_y[i][SECOND], y3 = dir_y[i][THIRD];
		if (field[x1][y1].what == ZERO && field[x2][y2].what == ZERO && field[x3][y3].what == ZERO ||
			field[x1][y1].what == CROSS && field[x2][y2].what == CROSS && field[x3][y3].what == CROSS)
		{
			*flag = FINISH; *Case = i;
			if (step == CROSS) result = WIN_CROSS;
			else if (step == ZERO) result = WIN_ZERO;
		}
	}
	if (*free_sq == 0 && result == NONE)
	{
		result = DRAW; *flag = FINISH;
	}
	return result;
}
