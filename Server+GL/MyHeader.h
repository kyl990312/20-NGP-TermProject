#pragma once 
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
