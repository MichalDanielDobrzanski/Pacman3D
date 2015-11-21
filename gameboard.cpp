#include "gameboard.h"
#include "glut.h"
#include <iostream>

// 0 - coin
// 1 - wall
// 2 - gate
// 3 - energizer
// 4 - ghost initial positions		
// 5 - intersections (there are also coins at them!)

int GameBoard::initial_map[GameBoard::DIM_Y][GameBoard::DIM_X] =
{  //0                   1         5         2                 29
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 0
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1}, // 1
	{1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,0,0,1,0,1}, // 2
	{1,3,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,1,1,0,1,3,1},
	{1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,4,0,1,0,1,1,1,0,0,0,1,0,1,0,1}, // 4

	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,0,1,0,1,0,1}, // 5
	{1,0,1,1,1,1,1,1,1,1,1,1,0,1,4,4,4,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1},

	{1,1,1,0,1,1,1,0,1,0,1,1,1,1,0,0,0,0,1,0,1,1,0,1,1,1,0,1,0,1}, // 10
	{1,3,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,3,1},
	{1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1,0,1,1,1,1,0,1}, // 12
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 13
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 14
};

GameBoard::GameBoard()
{
	wallThickness = 1;
	//std::copy(&initial_map[0][0],&initial_map[0][0] + DIM_X * DIM_Y, &current_coins_map[0][0]);

	//count the coins
	coinsCount = 0;
	for (int i = 0; i < DIM_X; i++)
	{
		for (int j = 0; j < DIM_Y; j++)
		{
			if (initial_map[j][i] == 0)
			{
				coinsCount++;
			}
		}
	}
}

void GameBoard::Draw()
{
	for (int i = 0; i < DIM_X; i++)
	{
		for (int j = 0; j < DIM_Y; j++)
		{
			if (initial_map[j][i] == 1) {
				// draw wall
				glColor3f(1,0,1);
				glPushMatrix();
					glTranslatef(i, DIM_Y - j - 1,CENTER_Z); // aby bylo 0-indeksowanie
					glutSolidSphere(wallThickness / 2,6,6);
				glPopMatrix();
			} else 
			if (initial_map[j][i] == 0 || initial_map[j][i] == 5 ) {
				// draw coins
				glColor3f(1,0,1/(float)(j + i));
				glPushMatrix();
					glTranslatef(i, DIM_Y - j - 1,CENTER_Z);
					glutSolidSphere(0.1,6,6);
				glPopMatrix();
			} else 
			if (initial_map[j][i] == 2) {
				// draw gate
				glPushMatrix();
					glTranslatef(i, DIM_Y - j - 1,CENTER_Z);
					glScalef(0.5f,0.5f,0.5f);
					glutSolidIcosahedron();
				glPopMatrix();
			} else 
			if (initial_map[j][i] == 3) {
				// draw energizers
				glPushMatrix();
					glTranslatef(i, DIM_Y - j - 1,CENTER_Z);
					//glScalef(0.5f,0.5f,0.5f);
					glutSolidTorus(0.1,0.4,10,10);
				glPopMatrix();
			}
		}
	}

}

bool GameBoard::isWall(int x, int y)
{
	int idx = DIM_Y - y - 1;
	//std::cout << "accessing: " <<  idx << "," << x << ", v: " << walls_map[idx][x] << std::endl;
	return (initial_map[idx][x] == 1 || initial_map[idx][x] == 2);
}
