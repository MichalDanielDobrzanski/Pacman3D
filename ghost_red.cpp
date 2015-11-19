#define _USE_MATH_DEFINES
#include <cmath>
#include "ghost_red.h"
#include "glut.h"
#include <iostream>

extern int initial_map[15][30];

GhostRed::GhostRed(int x, int y) : Ghost(x,y)
{
	index = 1;
	chase = true;
	scatter = false;
	frightened = false;
}

GhostRed::~GhostRed()
{

}

void GhostRed::Draw()
{
	//draw ghost
	glColor3f(1,1,0);
	glPushMatrix();
		glTranslatef(x,y,0.0);
		glRotatef(45,0,0,1);
		glutSolidCube(0.5);
	glPopMatrix();
}

// Blinky "shadow" movement algorithm
void GhostRed::Move() 
{
	// Regular Blinky Movement
	BasicMove();


	// check whether Blinky is at the regular turn:
	isAtTurn();

	// as for the intersection, make a decision based on his status
	if (chase) 
	{
		// he pursuits PackMan
		if (WallCheck(angle))
		{
			int counter = 3;
			if (!WallCheck(angle)) // no walls on the left
				counter--;
			if (!WallCheck(GetLeftAngle(angle))) // no walls on the left
				counter--;
			if (!WallCheck(GetRightAngle(angle))) // no walls on the right
				counter--;

			if (counter == 1 && abs(x - (int)x) < 0.1 && abs(y - (int)y < 0.1))
			{ // then this is surely an 2-outs intersection. Now pick the shortest way to the PackMan!

				std::cout << "Blinky: Intesection. x: " << x << std::endl;

				std::pair<int,int> optA = NextTile(GetLeftAngle(angle));  // left?
				std::pair<int,int> optB = NextTile(GetRightAngle(angle)); // or right?

				// figure it out!
				double optionA = abs(optA.first * optA.first - targetX * targetX) 
					+ abs(optA.second * optA.second  - targetY * targetY);
				double optionB = abs(optB.first * optB.first - targetX * targetX) 
					+ abs(optB.second * optB.second  - targetY * targetY);
				if (optionA <= optionB)
					angle = GetLeftAngle(angle);
				else
					angle = GetRightAngle(angle);

			}
		}
	} else
	if (scatter)
	{


	} else
	if (frightened)
	{

	}
}
