#include "ghost.h"
#include "gameboard.h"
#include "GLUT.H"


Ghost::Ghost()
{
	x 
}

void Ghost::Draw() 
{
	//draw current pacman
	glColor3f(1,1,0);
	glPushMatrix();
	glutSolidSphere(.5,10,10);
	glPopMatrix();

}

void Ghost::Move() 
{
}

