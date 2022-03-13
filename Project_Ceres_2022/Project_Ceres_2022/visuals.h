#pragma once

struct point
{
	float x, y, z;
	
};

struct face
{
	int vtx[3];
};

extern int globalWidth, globalHeight;

void Render();

void Resize(int w, int h);

void Setup();

void Idle();

void Keyboard(unsigned char key, int x, int y);

void RandomCoordinates(point*);

void DrawStars();

