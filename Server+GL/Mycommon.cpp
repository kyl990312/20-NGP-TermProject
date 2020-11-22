#include "MyCommon.h"

extern loadOBJ models[26];
extern Shader* shader1;

MyCommon::MyCommon() {
	std::cout << "creating River..." << std::endl;
	// init pos
	// only its z_pos will change in MyCommon()
	pos = { 0.0f,0.0f,0.0f };

	// init trees
	for (int i = 0; i < 3; ++i) {
		CreateTree(i);
	}
	// let's once make only 1 truck

	// init remaining variables
	moving = false;
	// please change
	// you have to change this value when you start map scrolling
	moving_degree = 0;
	collision_pos[0] = trees[0]->pos;
	collision_pos[1] = trees[1]->pos;
	collision_pos[2] = trees[2]->pos;
	obsRotation[0] = { 0.0f,90.0f,0.0f };
	obsSize[0] = { 1.f,1.f,1.f };
	obsTags[0] = 19;
	obsTags[1] = 19;
	obsTags[2] = 19;
	obs_cnt = 3;
	tag = 2;
	std::cout << "complete creating River!" << std::endl;
}

void MyCommon::draw(glm::mat4 projection, glm::mat4 view, Shader shader) {
	//loadOBJ obj(obj_path, shader.ID);
	//shader.use();
	shader1->use();
	models[12].load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));

	models[12].setTransform(model);

	models[12].draw();
	for (int i = 0; i < 3; i++)
		trees[i]->draw(projection, view, model, shader);
}

void MyCommon::move() {
	// make trees move
	// make road move
	if (moving) {

	}
}

bool MyCommon::check_removing() {

	// check its position_y.
	// if it out off the screen, request removing to state_class
	if (pos.z > 600) {
		for (int i = 0; i < 3; ++i)
			remove_tree(i);
		return true;
	}
	return false;
}

void MyCommon::CreateTree(int idx) {
	trees[idx] = new MyTree(pos);
}

void MyCommon::remove_tree(int i) {
	delete trees[i];
}

MyCommon::~MyCommon() {};
