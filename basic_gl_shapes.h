#ifndef BASIC_GL_SHAPES_H
#define BASIC_GL_SHAPES_H

#include "glut.h"

// vertices arrays:
// Szescian:

namespace
{

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

}

#endif