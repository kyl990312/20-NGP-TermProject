#include "MyRiver.h"

extern loadOBJ models[26];
extern Shader* shader1;

MyRiver::MyRiver() {
	std::cout << "creating River..." << std::endl;
	// init pos
	// only its z_pos will change in MyRiver()
	pos = { 0.0f,0.0f,0.0f };

	// init logs
	for (int i = 0; i < 3; ++i) {
		CreateLog(i);
	}
	// let's once make only 1 truck

	// init remaining variables
	moving = false;
	// please change
	// you have to change this value when you start map scrolling
	collision_pos[0] = logs[0]->pos;
	collision_pos[1] = logs[1]->pos;
	collision_pos[2] = logs[2]->pos;
	obsRotation[0] = { 0.0f,90.0f,0.0f };
	obsSize[0] = { 1.f,1.f,1.f };
	obsTags[0] = 20;
	obsTags[1] = 20;
	obsTags[2] = 20;
	moving_degree = 0;
	obs_cnt = 3;
	tag = 1;
	std::cout << "complete creating River!" << std::endl;
}

void MyRiver::draw(glm::mat4 projection, glm::mat4 view, Shader shader) {
	//loadOBJ obj(obj_path, shader.ID);
	//shader.use();

	shader1->use();
	models[14].load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));

	models[14].setTransform(model);

	models[14].draw();
	for (int i = 0; i < 3; i++)
		logs[i]->draw(projection, view, model, shader);
}

void MyRiver::move() {
	// make logs move
	for (int i = 0; i < 3; ++i) {
		logs[i]->move(pos);
		collision_pos[i] = logs[i]->pos;
		if (logs[i]->check_removing())
			remove_log(i);
	}

	// make road move
	if (moving) {

	}
}

bool MyRiver::check_removing() {

	// check its position_y.
	// if it out off the screen, request removing to state_class
	if (pos.z > 600) {
		for (int i = 0; i < 3; ++i)
			remove_log(i);
		return true;
	}
	return false;
}

void MyRiver::CreateLog(int idx) {
	logs[idx] = new MyLog(pos, speed);
}

void MyRiver::remove_log(int i) {
	// 1. delete
	delete logs[i];

	// 2. create
	if (pos.z <= 600)
		logs[i] = new MyLog(pos, speed);
}

MyRiver::~MyRiver() {};


float MyRiver::get_obs_speed(int idx) {
	return logs[idx]->speed;
}