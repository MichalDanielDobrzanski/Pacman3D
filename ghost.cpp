#define _USE_MATH_DEFINES
#include <cmath>

#include "ghost.h"
#include "gameboard.h"
#include "GLUT.H"

Ghost::Ghost(int tx, int ty)
{
	angle = 180; // initially all ghosts move to the left
	moving = true;
	speed = 0.07;


	x = tx;
	y = ty;
	if (index == 1)
	{
		// red ghost
		scatterX = GameBoard::DIM_X - 2;
		scatterY = GameBoard::DIM_Y + 4;
	}
}

void Ghost::Draw() 
{
	//draw ghost
	glColor3f(1,1,0);
	glPushMatrix();
		glTranslatef(x,y,0.0);
		glutSolidCube(0.7);
	glPopMatrix();

}


// basic movement algorithm which applies to every ghost
void Ghost::BasicMove()
{
	// ghost regular movement
	x +=  speed*cos(M_PI/180*angle); // dodawany jakis staly interwal
	y +=  speed*sin(M_PI/180*angle);
}

