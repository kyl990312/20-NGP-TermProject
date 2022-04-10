#pragma once 
#include <glew.h>
#include <freeglut.h>
#include <freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

struct MyBoundingBox {
	float right, top, front, left, bottom, back;
};

#define SPEED 10
