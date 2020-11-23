#pragma once 
#define SCR_WIDTH 800
#define SCR_HEIGHT 600

struct MyPos {
	float x;
	float y;
	float z;
};

struct MyBoundingBox {
	float right, top, front, left, bottom, back;
};

#define SPEED 10
