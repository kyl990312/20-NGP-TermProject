#include "Title_State.h"

extern loadOBJ models[27];
extern Shader* shader1;
extern Shader* fontShader;
extern Shader* startbutton_shader;

void Title_State::Display() {
	shader1->use();
	// lightning
	draw_rabit();

	fontShader->use();
	fontShader->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	fontShader->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	fontShader->setVec3("lightPos", glm::vec3(0, 800, 2000));
	fontShader->setVec3("obj_color", glm::vec3(1.0, 0.6, 0.0));
	draw_font();

	startbutton_shader->use();
	startbutton_shader->setVec3("obj_color", glm::vec3(1.0, 0.5, 0.0));
	draw_startbutton();
}

void Title_State::update() {
	font_sin_angle = (float)(((int)font_sin_angle + 5) % 180);
	obj_pos.z = 50 * sin(glm::radians(font_sin_angle));
}

void Title_State::keyboard(unsigned char key, int x, int y) {
	switch (key) {
	default:
		next_state = 1;
		break;
	}
}

void Title_State::mouse(int button, int state, int x, int y) {
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

	//if (ready_state == 1)
	//	startbutton_shader->setVec3("obj_color", glm::vec3(1.0, 0.5, 0.8));
	models[26].load(projection, view);

	models[26].setTransform(model);
	models[26].draw();
}

void Title_State::TitleDatas(ObjectData mapdatas[]) {
	for (int i = 0; i < 100; ++i) {
		mapdatas[i].tag = -1;
	}

	ObjectData tmpMap;

	tmpMap.tag = ModelIdx::Hero;
	tmpMap.positionX = 300.0f;
	tmpMap.positionY = 0.f;
	tmpMap.positionZ = obj_pos.z;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[0] = tmpMap;

	tmpMap.tag = ModelIdx::TitleFont;
	tmpMap.positionX = 0.f;
	tmpMap.positionY = 0.f;
	tmpMap.positionZ = obj_pos.z;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 1.0f;
	tmpMap.sizeY = 1.0f;
	tmpMap.sizeZ = 1.0f;
	mapdatas[1] = tmpMap;

	tmpMap.tag = ModelIdx::StartButton;
	tmpMap.positionX = 10.0f;
	tmpMap.positionY = -300.0f;
	tmpMap.positionZ = 10.0f;
	tmpMap.rotationX = 60.0f;
	tmpMap.rotationY = 6.0f;
	tmpMap.rotationZ = -27.0f;
	tmpMap.sizeX = 3.5f;
	tmpMap.sizeY = 4.0f;
	tmpMap.sizeZ = 4.0f;
	mapdatas[2] = tmpMap;
}
