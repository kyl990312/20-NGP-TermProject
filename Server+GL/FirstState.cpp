#include "FirstState.h"
#include "FirstState.h"

extern loadOBJ models[26];
extern Shader* shader1;

FirstState::FirstState() {

	// init pos
	// only its z_pos will change in FirstState()
	pos = { 0.0f,0.0f,0.0f };

	// init remaining variables
	moving = false;
	// please change
	// you have to change this value when you start map scrolling
	moving_degree = 0;
	collision_pos[0] = {0.0f};
	collision_pos[1] = {0.0f};
	collision_pos[2] = {0.0f};
	obs_cnt = 0;
	tag = 2;
}

void FirstState::draw(glm::mat4 projection, glm::mat4 view, Shader shader) {
	//loadOBJ obj(obj_path, shader.ID);
	//shader.use();
	shader1->use();
	models[12].load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));

	models[12].setTransform(model);

	models[12].draw();
}

void FirstState::move() {
	// make trees move
	// make road move
	if (moving) {

	}
}

bool FirstState::check_removing() {

	// check its position_y.
	// if it out off the screen, request removing to state_class
	if (pos.z > 600) {
		return true;
	}
	return false;
}


FirstState::~FirstState() {};
