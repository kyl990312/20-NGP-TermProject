#pragma once
#include<list>
#include <fstream>
#include "loadObj.h"
#include "MyHeader.h"

class End_State
{
public:
	int next_state = 2;
	glm::mat4 projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-600, (float)600);
	glm::vec3 cameraPos = glm::vec3(5.0f, 35.0f, 40);
	glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	std::list<int> rank;
	int cur_score;
	int best_score;
	int mid_score;
	int last_score;
	Shader* shader1 = nullptr;
	int num[3] = { 0, };

public:
	End_State();
	~End_State();
	void Display();
	void update();
	void keyboard(unsigned char key, int x, int y);
	void draw_score(float y_pos, int score);
	void first_number(float y_pos);
	void second_number(float y_pos);
	void third_number(float y_pos);
};

