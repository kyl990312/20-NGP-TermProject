#pragma once
#include "loadObj.h"
#include "MyHeader.h"
#include"firework_particle.h"
#include "DataStruct.h"

#include <math.h>
class Title_State
{
public:
	glm::mat4 projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-600, (float)600);
	glm::vec3 cameraPos = glm::vec3(8.0f, 45.0f, 40);
	glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	MyPos obj_pos = { 0.0f,0.0f,0.0f };
	Shader* shader;
	Shader* font_shader;
	Shader* startbutton_shader;

	firework firework_particle[4];

	float font_sin_angle = 0.0f;
	int next_state = 0;
	int clientCnt = 0;

public:
	void Display();
	void update();
	void keyboard(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void draw_font();
	void draw_rabit();
	void draw_startbutton();
	void TitleDatas(ObjectData[]);
};
