#pragma once

#define FIRST 0
#define SECOND 1
#define THIRD 2
#define SIZE 3
#define PARITY 2
#define OUTLINE 8
#define NONE -1
#define SIZE_SQUARE 250
#define SHIFT_1 75
#define SHIFT_2 300
#define COUNT 6
#define CASES 8

enum WHAT { EMPTY, CROSS, ZERO };
enum RESULT { WIN_ZERO, WIN_CROSS, DRAW };
enum STATES { ON, OFF, GAME, FINISH };
enum LINES { G1, G2, G3, V1, V2, V3, DM, DS };
typedef struct square {
	int what;
	int color;
}SQUARE;

void InitField(SQUARE field[][SIZE]);
void FindSquare(SQUARE field[][SIZE], int mouseX, int mouseY, int* x, int* y);
int CheckSbWin(SQUARE field[][SIZE], int step, int* flag, int* free_sq, int* Case);