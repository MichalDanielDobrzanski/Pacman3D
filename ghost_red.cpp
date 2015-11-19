#include "ghost_red.h"
#include "glut.h"

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
	BasicMove();

	if (chase) 
	{

	} else
	if (scatter)
	{


	} else
	if (frightened)
	{

	}
}
