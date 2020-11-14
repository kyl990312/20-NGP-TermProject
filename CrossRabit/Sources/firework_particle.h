#pragma once
#include "loadObj.h"
#include"shader.h"
#include "MyHeader.h"

#define M_PI 3.14159265358979323846

class firework {
public:
	glm::mat4 projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-600, (float)600);
	glm::vec3 cameraPos = glm::vec3(8.0f, 45.0f, 40);
	glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	float color_random1, color_random2, color_random3, X, Y;

	struct snowPos {
		float X = 0, Y = 200, Z = 100, timer = 10, dir = rand() % 360, speed = rand() % 10 + 2;
	};
	snowPos snow[50];

	firework();

	void draw();

};