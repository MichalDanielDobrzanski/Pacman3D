#define _USE_MATH_DEFINES
#include <cmath>

#include "basic_gl_shapes.h"
#include "ghost.h"
#include "gameboard.h"
#include "GLUT.H"
#include <iostream>
#include <vector>
#include <exception>


Ghost::Ghost(float tr, float tg, float tb, int tx, int ty, float tz) : Creature(tx,ty,tz)
{
	angle = 180; // initially all ghosts move to the left
	speed = 0.03;

	r = tr;
	g = tg;
	b = tb;

	if (index == 1)
	{
		// red ghost
		scatterTileX = GameBoard::DIM_X - 2;
		scatterTileY = GameBoard::DIM_Y + 4;
	}
}

// Ghost appearance.
void Ghost::Draw(float phi) 
{
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushMatrix();
		// overall ghost parameters:
		glTranslatef(x,y,z / 10);
		glColor3f(r,g,b);
		glScalef(0.25,0.25,0.05);
		//glRotatef(phi * 90,0,sin(phi),cos(phi)); // fix this
		glPushMatrix();
			glScalef(0.2,0.2,1);
			glPushMatrix(); // solid body
				glPushMatrix();
					glScalef(2,0.5,1);
					glTranslatef(0,17,0);
					Block();
				glPopMatrix();
				glPushMatrix();
					glScalef(4,1,1);
					glTranslatef(0,7,0);
					Block();
				glPopMatrix();
				glPushMatrix();
					glScalef(6,1.5,1);
					glTranslatef(0,3,0);
					Block();
				glPopMatrix();
				glPushMatrix();
					glScalef(7,3,1);
					Block();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix(); // details
				glPushMatrix(); // top details
					glTranslatef(4.5,6.5,0);
					glScalef(0.5,0.5,1);
					Block();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-4.5,6.5,0);
					glScalef(0.5,0.5,1);
					Block();
				glPopMatrix();
				glPushMatrix(); // bot detals
					glTranslatef(2,-4,0);
					glScalef(1,1,1);
					Block();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-2,-4,0);
					glScalef(1,1,1);
					Block();
				glPopMatrix();
				glPushMatrix(); // bot details 2
					glTranslatef(3.5,-3.5,0);
					glScalef(0.5,0.5,1);
					Block();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-3.5,-3.5,0);
					glScalef(0.5,0.5,1);
					Block();
				glPopMatrix();
				glPushMatrix(); // bot details 3
					glTranslatef(6,-3.5,0);
					glScalef(1,0.5,1);
					Block();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-6,-3.5,0);
					glScalef(1,0.5,1);
					Block();
				glPopMatrix();
					glPushMatrix(); // bot details 4
					glTranslatef(6.5,-4.5,0);
					glScalef(0.5,0.5,1);
					Block();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-6.5,-4.5,0);
					glScalef(0.5,0.5,1);
					Block();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

// Not ufeful as for now
void Ghost::onTileChange()
{
	//std::cout << "Ghost tile: " << tileX << ", " << tileY << std::endl;	
}

bool Ghost::WallCheck(int agle)
{
	if (agle == 0)
		return GameBoard::isWall(tileX + 1,tileY);
	if (agle == 180)
		return GameBoard::isWall(tileX - 1,tileY);
	if (agle == 90)
		return GameBoard::isWall(tileX,tileY + 1);
	if (agle == 270)
		return GameBoard::isWall(tileX,tileY - 1);
}

// ghost left hand direction
double GetLeftAngle(double angdir)
{
	if ((int)angdir + 90 == 360)
		return 0;
	else
		return angdir + 90;
}

// ghost right hand direction
double GetRightAngle(double angdir)
{
	if ((int)angdir - 90 == -90)
		return 270;
	else
		return angdir - 90;
}

int Ghost::TargetPythagoras(int agle)
{
	int tx = 0;
	int ty = 0;

	if (agle == 0)
	{
		tx = tileX + 1;
		ty = tileY;
	}
	if (agle == 180)
	{
		tx = tileX - 1;
		ty = tileY;
	}
	if (agle == 90)
	{
		tx = tileX;
		ty = tileY + 1;
	}
	if (agle == 270)
	{
		tx = tileX;
		ty = tileY - 1;

	}
	return abs(tx * tx - targetTileX * targetTileX) + abs(ty * ty - targetTileY * targetTileY);
}

// Here we will make a decision where should ghost go.
void Ghost::onTileCenter()
{
	moving = false;
	PadToCenter();

	//std::cout << "Ghost at center of tile coords: " << x << ", " << y << std::endl;
	//std::cout << "Ghost at center of tile: " << tileX << ", " << tileY << std::endl;

	// Dealing with intersections:
	std::vector<int> dist(3,10000);

	if (!WallCheck(angle))
	{
		dist[0] = TargetPythagoras(angle);
		//std::cout << "Ghost front dist: " << dist[0] << std::endl;
	}
	if (!WallCheck(GetLeftAngle(angle)))
	{
		dist[1] = TargetPythagoras(GetLeftAngle(angle));
		//std::cout << "Ghost left dist: " << dist[1] << std::endl;
	}
	if (!WallCheck(GetRightAngle(angle)))
	{
		dist[2] = TargetPythagoras(GetRightAngle(angle));
		//std::cout << "Ghost right dist: " << dist[2] << std::endl;
	}

	//std::cout << "Ghost Fdist: " << dist[0] << ", Ldist: " << dist[1] << ", Rdist" << dist[2] << std::endl;

	int smallest = dist[0];
	int idx = 0;
	for (int i = 1; i < dist.size(); i++) 
	{
		if (dist[i] < smallest)
		{
			smallest = dist[i];
			idx = i;
		}
	}

	try { if (smallest == 10000) throw 99; } 
	catch (int e) { std::cout << "Exception " << e << ": THERE CANT BE ANY DEAD CORRIDORS IN THE MAP "  << '\n'; }

	if (idx == 1)
		angle = GetLeftAngle(angle);
	else
	if (idx == 2)
		angle = GetRightAngle(angle);

	moving = true;	
}

