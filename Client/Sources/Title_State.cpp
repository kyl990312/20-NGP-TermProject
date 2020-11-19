#include "Title_State.h"

extern loadOBJ models[27];
extern Shader* shader1;

void Title_State::Display() {
	shader1->use();
	// lightning
	draw_rabit();

	font_shader->use();
	font_shader->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	font_shader->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	font_shader->setVec3("lightPos", glm::vec3(0, 800, 2000));
	font_shader->setVec3("obj_color", glm::vec3(1.0, 0.6, 0.0));
	draw_font();
	
	startbutton_shader->use();
	startbutton_shader->setVec3("obj_color", glm::vec3(1.0, 0.5, 0.0));
	draw_startbutton();

	for (int i = 0; i < 4; i++)
		firework_particle[i].draw();
}

void Title_State::update() {
	font_sin_angle = (float)(((int)font_sin_angle + 5) % 180);
	obj_pos.z = 50*sin(glm::radians(font_sin_angle));
}

void Title_State::mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN
		&& x < 550 && x > 410
		&& y < 600 && y >470) {
		ready_state = 1;
	}
}

void Title_State::draw_font() {	
	models[23].load(projection, view);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);	

	// transform
	translation = glm::translate(translation, glm::vec3(obj_pos.x, obj_pos.y, obj_pos.z));
	scaling = glm::scale(scaling, glm::vec3(1.0f, 1.0f, 1.0f));
	model = scaling * translation;
	models[23].setTransform(model);

	models[23].draw();
}

void Title_State::draw_rabit()
{
	models[0].load(projection, view);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	// transform
	translation = glm::translate(translation, glm::vec3(300, obj_pos.y, obj_pos.z));
	scaling = glm::scale(scaling, glm::vec3(3.0f, 3.0f, 3.0f));
	model = translation * scaling;
	models[0].setTransform(model);

	models[0].draw();
}

void Title_State::draw_startbutton()
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	// transform
	translation = glm::translate(translation, glm::vec3(0, -300, 0));
	scaling = glm::scale(scaling, glm::vec3(3.5f, 4.0f, 4.0f));
	
	model = translation * scaling;
	model = glm::rotate(model, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(6.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	if (ready_state == 1)
		startbutton_shader->setVec3("obj_color", glm::vec3(1.0, 0.5, 0.8));
	models[26].load(projection, view);

	models[26].setTransform(model);
	models[26].draw();
}