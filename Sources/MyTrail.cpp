#include "MyTrail.h"
#include<iostream>

MyTrail::MyTrail() {
	std::cout << "creating Trail..." << std::endl;
	// init pos
	// only its z_pos will change in MyTrail()
	pos = { 0.0f,0.0f,0.0f };

	// init trains
	CreateTrain(0);
	
	// let's once make only 1 truck
	//CreateTruck(0);

	// init remaining variables
	moving = false;
	// please change
	// you have to change this value when you start map scrolling
	moving_degree = 0;
	moving_degree = 0;
	collision_pos[1] = { -800,-800,-800 };
	collision_pos[2] = { -800,-800,-800 };
	obs_cnt = 1;
	tag = 3;
	std::cout << "complete creating trail!" << std::endl;
}

void MyTrail::draw(glm::mat4 projection, glm::mat4 view, Shader shader) {
	loadOBJ obj(obj_path, shader.ID);
	shader.use();
	obj.load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
	obj.setTransform(model);

	obj.draw();
	train_warning_light(projection, view);
	trains[0]->draw(projection, view, model, shader);
}

void MyTrail::move() {
	// make trains move
	trains[0]->move(pos);
	collision_pos[0] = trains[0]->pos;
	if (trains[0]->check_removing())
		remove_train(0);
	
	if (moving) {

	}
}

bool MyTrail::check_removing() {
	// check its position_y.
	if (pos.z > 600) {
		remove_train(0);
		return true;
	}
	// if it out off the screen, request removing to state_class
	return false;
}

void MyTrail::CreateTrain(int idx) {
	trains[idx] = new MyTrain(pos);
}

void MyTrail::remove_train(int i) {
	// 1. delete
	delete trains[i];

	// 2. create
	if (pos.z <= 600)
		trains[i] = new MyTrain(pos);
}


void MyTrail::train_warning_light(glm::mat4 projection, glm::mat4 view)
{
	Shader light("shaders/trainwarningvertex.glvs", "shaders/trainwarningfragment.glfs"); // you can name your shader files however you like

	light.use();

	loadOBJ lightbox("Resources/box.obj", light.ID);

	lightbox.load(projection, view);

	//За·Д
	glm::mat4 transMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatix = glm::mat4(1.0f);
	glm::mat4 myTransformeVector = glm::mat4(1.0f);
	glm::vec3 lightColor = glm::vec3(1.0f);

	transMatrix = glm::translate(transMatrix, glm::vec3(0.0f, 0.0f, pos.z));
	scaleMatix = glm::scale(scaleMatix, glm::vec3(20.0f, 21.0f, 20.0f));

	myTransformeVector = transMatrix * scaleMatix;
	lightbox.setTransform(myTransformeVector);

	if (trains[0]->pos.x > -1500)
		lightColor = glm::vec3(1.0f, 0.0f, 0.0f);
	if (trains[0]->pos.x > 600)
		lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	light.setVec3("lightColor", lightColor);

	lightbox.draw();
}

MyTrail::~MyTrail() {};
