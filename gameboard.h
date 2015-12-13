#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <windows.h>
#include "resource.h"

class GameBoard {

public:
	// general map information:
	static const int DIM_X = 30;
	static const int DIM_Y = 15;
	static const int CENTER_X = DIM_X / 2;
	static const int CENTER_Y = (DIM_Y + 1) / 2;
	static const int CENTER_Z = 0;

	int coinsCount;

	// static map references:
	static int initial_map[DIM_Y][DIM_X];
	static bool isWall(int x, int y);

	// tekstury
	BITMAP BM;

	GameBoard();

	// map visual appearance:
	void Draw();
	void DrawWall(int x, int y, int z);
	void DrawWalls(int j, int i);

	void TextureLoad(int id);
};

#endif