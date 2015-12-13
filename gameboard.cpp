#include "gameboard.h"
#include "glut.h"
#include <iostream>
#include <vector>

using namespace std;

// Zmienne do kontroli animacji monet:
int coinAngle = 0;

// 0 - coin
// 1 - wall
// 2 - gate
// 3 - energizer
// 4 - ghost initial positions		

int GameBoard::initial_map[GameBoard::DIM_Y][GameBoard::DIM_X] =
{  //0                   1         5         2                 29
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 0
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1}, // 1
	{1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,0,0,1,0,1}, // 2
	{1,3,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,3,1},
	{1,0,1,0,1,1,1,0,1,1,1,1,0,0,0,4,0,1,0,1,1,1,0,0,0,1,0,1,0,1}, // 4

	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,0,1,0,1,0,1}, // 5
	{1,0,1,1,1,1,1,1,1,1,1,1,0,1,4,4,4,1,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,1},

	{1,1,1,0,1,1,1,0,1,0,1,1,1,1,0,0,0,0,1,0,1,1,0,1,1,1,0,1,0,1}, // 10
	{1,3,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,3,1},
	{1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1,0,1,1,1,1,0,1}, // 12
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 13
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 14
};


// vertices arrays:
// Szescian:
GLfloat vertices[] = {  1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
                        1, 1, 1,   1,-1, 1,   1,-1,-1,   1, 1,-1,   // v0,v3,v4,v5 (right)
                        1, 1, 1,   1, 1,-1,  -1, 1,-1,  -1, 1, 1,   // v0,v5,v6,v1 (top)
                       -1, 1, 1,  -1, 1,-1,  -1,-1,-1,  -1,-1, 1,   // v1,v6,v7,v2 (left)
                       -1,-1,-1,   1,-1,-1,   1,-1, 1,  -1,-1, 1,   // v7,v4,v3,v2 (bottom)
                        1,-1,-1,  -1,-1,-1,  -1, 1,-1,   1, 1,-1 }; // v4,v7,v6,v5 (back)

GLfloat vertices2[] = {  0, 0,   1,   0,-0.5, 1,  1, 0,   1,              // (front)
                         0,-0.5, 1,   0,-0.5,-1,  1, 0,  -1,   1,  0, 1,  // (right)
                         1, 0,   1,   1, 0,  -1,  0, 0,  -1,   0,  0, 1,  // (top)
                         0, 0,   1,   0, 0,  -1,  0,-0.5,-1,   0,-0.5,1,  // (left)
						 0,-0.5,-1,   1, 0,  -1,  0, 0,  -1             };// (back)

GLfloat vertices3[] = {  0, 0,  1,   0,0.5, 1,  1, 0,  1,           // (front)
                         0,0.5, 1,   0,0.5,-1,  1, 0, -1, 1, 0, 1,  // (right)
                         1, 0,  1,   1, 0, -1,  0, 0, -1, 0, 0, 1,  // (top)
                         0, 0,  1,   0, 0, -1,  0,0.5,-1, 0,0.5,1,  // (left)
						 0,0.5,-1,   1, 0, -1,  0, 0, -1          };// (back)

// normals arrays:
GLfloat normals[]  = {  0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
                       -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
                        0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
                        0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)

GLfloat normals2[]  = { 0, 0, 1,   0, 0, 1,   0, 0, 1,			   //  (front)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,  //  (right)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,  //  (top)
                       -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  //  (left)
                        0, 0,-1,   0, 0,-1,   0, 0,-1            };//  (back)

GLfloat normals3[]  = { 0, 0, 1,   0, 0, 1,   0, 0, 1,			   //  (front)
                        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,  //  (right)
                        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,  //  (top)
                       -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  //  (left)
                        0, 0,-1,   0, 0,-1,   0, 0,-1            };//  (back)

// colors arrays:
GLfloat colors[]   = {  1, 0, 1,   1, 0, 1,  1, 0, 1,   1, 0, 1,   // v0,v1,v2,v3 (front)
                        1, 0, 1,   1, 0, 1,  1, 0, 1,   1, 0, 1,   // v0,v3,v4,v5 (right)
                        1, 0, 1,   1, 0, 1,  1, 0, 1,   1, 0, 1,   // v0,v5,v6,v1 (top)
                        1, 0, 1,   1, 0, 1,  1, 0, 1,   1, 0, 1,   // v1,v6,v7,v2 (left)
                        1, 0, 1,   1, 0, 1,  1, 0, 1,   1, 0, 1,   // v7,v4,v3,v2 (bottom)
                        1, 0, 1,   1, 0, 1,  1, 0, 1,   1, 0, 1 }; // v4,v7,v6,v5 (back)

GLfloat colors2[]   = { 1, 0, 1,   1, 0, 1,  1, 0, 1,             // (front)
                        1, 0, 1,   1, 0, 1,  1, 0, 1,   1, 0, 1,  // (right)
                        1, 0, 1,   1, 0, 1,  1, 0, 1,   1, 0, 1,  // (top)
                        1, 0, 1,   1, 0, 1,  1, 0, 1,   1, 0, 1,  // (left)
					    1, 0, 1,   1, 0, 1,  1, 0, 1            };// (back)

// index arrays of vertexes:
GLubyte indices[]  = { 0, 1, 2,   2, 3, 0,      // front
                       4, 5, 6,   6, 7, 4,      // right
                       8, 9,10,  10,11, 8,      // top
                      12,13,14,  14,15,12,      // left
                      16,17,18,  18,19,16,      // bottom
                      20,21,22,  22,23,20 };    // back

GLubyte indices2[] = { 0, 1, 2,			      // front
                       3, 4, 5,   3, 5, 6,    // right
                       7, 8, 9,   7, 9, 10,   // top
                      11,12,13,   11,13,14,   // left
                      17,15,16             }; // back

GLubyte indices3[] = { 0, 2, 1,				  // front
                       3, 6, 5,   3, 5, 4,    // right
                       7, 8, 9,   7, 9, 10,   // top, right
                      11,14,13,   11,13,12,   // left
                      15,17,16             }; // back


// textures:
GLfloat textures[] = {  0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0
					 };

// Wspolne wspolrzedne tekstury dla zbudowanej figury dla konca muru.
GLfloat textures2[] = { 0.0,0.0, 0.5,0.0, 1.0,0.25, 1.0,0.75, 0.5,1.0, 0.0,1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0,
						0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0, 1.0
					 };


void GameBoard::TextureLoad(int id)
{
	HBITMAP Bitmap = NULL;
	HINSTANCE myInstance = GetModuleHandle(NULL);

	Bitmap = (HBITMAP)LoadImage(myInstance,MAKEINTRESOURCE(id),IMAGE_BITMAP,0,0, LR_CREATEDIBSECTION);
	GetObject(Bitmap,sizeof(BM),&BM);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // wiecej pikseli, jak jestesmy blizej obiektu
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // mniej pikseli im dalej

	// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,BM.bmWidth,BM.bmHeight,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,BM.bmBits);

	DeleteObject((HGDIOBJ) Bitmap);
}

// draw wall with vertex arrays - http://www.songho.ca/opengl/gl_vertexarray.html
void GameBoard::DrawWall(int x, int y, int z)
{
	glEnable(GL_TEXTURE_2D);

	// ustawienia funkcji teksturu
	// co one powoduja? ? GL_REPLACE ? GL _MODULATE
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glTexCoordPointer(2,GL_FLOAT,0,textures);
	glNormalPointer(GL_FLOAT, 0, normals);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glPushMatrix();
		glTranslatef(x,y,z);
		glScalef(0.5,0.5,0.2);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
    glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glDisable(GL_TEXTURE_2D);
}

// Graniastos³up o podstawie trójk¹ta.
void Triang()
{
	glVertexPointer(3,GL_FLOAT,0,vertices2);
	glNormalPointer(GL_FLOAT,0,normals2);
	glColorPointer(3,GL_FLOAT,0,colors2);
	glPushMatrix();
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, indices2);
	glPopMatrix();
}

// Drugi graniastos³up o podstawie trójk¹ta.
void Triang2()
{
	glVertexPointer(3,GL_FLOAT,0,vertices3);
	glNormalPointer(GL_FLOAT,0,normals2);
	glColorPointer(3,GL_FLOAT,0,colors2);
	glPushMatrix();
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, indices3);
	glPopMatrix();
}

// Szescian o szerokosci 2.
void Block()
{
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glNormalPointer(GL_FLOAT,0,normals);
	glColorPointer(3,GL_FLOAT,0,colors);
	glPushMatrix();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	glPopMatrix();
}

// Koniec muru.
void DrawWallEnd(int x, int y, int z, int angle)
{
	// Okreslenie wspolnej tesktury.
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2,GL_FLOAT,0,textures);

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPushMatrix();
		glTranslatef(x,y,z);
		glScalef(0.5,0.5,0.4);
		glRotatef(angle + 90,0,0,1);
		glPushMatrix();
			glPushMatrix();
				glTranslatef(-0.5,0.5,0); // block 1
				glScalef(0.5,0.5,0.5);
				Block();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.5,-0.5,0); // block 2
				glScalef(0.5,0.5,0.5);
				Block();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.5,0,0); // block 3
				glScalef(0.5,0.5,0.5);
				Block();
			glPopMatrix();
			glPushMatrix(); // 1st triang
				glScalef(1,1,0.5);
				glTranslatef(0,-0.5,0);
				Triang();
			glPopMatrix();
			glPushMatrix(); // 2nd triang
				glTranslatef(0,0.5,0);
				glScalef(1,1,0.5);
				Triang2();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_TEXTURE_2D);
}

GameBoard::GameBoard()
{
	//count the coins
	coinsCount = 0;
	for (int i = 0; i < DIM_X; i++)
	{
		for (int j = 0; j < DIM_Y; j++)
		{
			if (initial_map[j][i] == 0)
				coinsCount++;
		}
	}
	// zaladuj teksture.
	TextureLoad(ID_2);
}

void GameBoard::Draw()
{
	static int coinStep = 1;
	coinStep = (coinStep + 1) % 360;
	
	for (int i = 0; i < DIM_X; i++)
	{
		for (int j = 0; j < DIM_Y; j++)
		{
			// wall drawing
			DrawWalls(j,i);

			if (initial_map[j][i] == 0) 
			{
				// draw coins
				glPushMatrix();
					glColor3f(1,0,1/(float)(j + i));
					glTranslatef(i, DIM_Y - j - 1,CENTER_Z);
					glRotatef(coinStep + (i * j),0,1,0);
					glScalef(1.0,1.0,2.0);
					glutSolidSphere(0.1,6,6);
				glPopMatrix();
			} else 
			if (initial_map[j][i] == 2) 
			{
				// draw gate
				glPushMatrix();
					glTranslatef(i, DIM_Y - j - 1,CENTER_Z);
					glScalef(0.5f,0.5f,0.5f);
					glutSolidIcosahedron();
				glPopMatrix();
			} else 
			if (initial_map[j][i] == 3) 
			{
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

void GameBoard::DrawWalls(int j, int i)
{
	if (initial_map[j][i] == 1) 
	{ // wall drawing algorithm
		if (j > 0 && j < DIM_Y - 1 && i > 0 && i < DIM_X - 1) 
		{
			int counter = 0;
			int angle = -1;
			if (initial_map[j + 1][i] <= 0)
				counter++;
			else
				angle = 0;
			if (initial_map[j][i + 1] <= 0)
				counter++;
			else
				angle = 90;
			if (initial_map[j - 1][i] <= 0)
				counter++;
			else 
				angle = 180;
			if (initial_map[j][i - 1] <= 0)
				counter++;
			else
				angle = 270;
			if (counter > 2)
			{
				DrawWallEnd(i, DIM_Y - j - 1,CENTER_Z, angle);
			}
			else
				DrawWall(i, DIM_Y - j - 1,CENTER_Z);
		}
		else
			DrawWall(i, DIM_Y - j - 1,CENTER_Z);
	}
}

// Perform checking whether there is a wall on specific tile (described as x,y)
bool GameBoard::isWall(int x, int y)
{
	int idx = DIM_Y - y - 1;
	//std::cout << "accessing: " <<  idx << "," << x << ", v: " << walls_map[idx][x] << std::endl;
	return (initial_map[idx][x] == 1 || initial_map[idx][x] == 2);
}
