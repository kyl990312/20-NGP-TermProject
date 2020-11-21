#include "MyRoad.h"
#include<iostream>

extern loadOBJ models[26];
extern Shader* shader1;

MyRoad::MyRoad() {
	std::cout << "creating Road..." << std::endl;
	// init pos
	// only its z_pos will change in MyRoad()
	pos = { 0.0f,0.0f,0.0f };

	// init trucks
	for (int i = 0; i < 2; ++i) {
		CreateTruck(i);
	}
	// let's once make only 1 truck
	//CreateTruck(0);

	// init remaining variables
	moving = false;
	tag = 4;
	// please changeg
	moving_degree = 0;
	collision_pos[0] = trucks[0]->pos;
	collision_pos[1] = trucks[0]->pos;
	collision_pos[2] = { -800,-800,-800 };
	obs_cnt = 2;
	std::cout << "complete creating road!" << std::endl;
}

 void MyRoad::draw(glm::mat4 projection, glm::mat4 view, Shader shader)  {
	 //loadOBJ obj(obj_path, shader.ID);
	 shader1->use();
	 models[13].load(projection, view);

	 glm::mat4 model = glm::mat4(1.0f);
	 
	 // change road's positoin 
	 model = glm::translate(model,glm::vec3(pos.x, pos.y, pos.z));
	 models[13].setTransform(model);
	
	 models[13].draw();
	 for (int i = 0; i < 2; ++i)
		trucks[i]->draw(projection, view, model, shader);
}

 void MyRoad::move() {
	 // make trucks move
	 for (int i = 0; i < 2; ++i) {
		 trucks[i]->move(pos);
		 collision_pos[i] = trucks[i]->pos;
		 if (trucks[i]->check_removing())
			 remove_truck(i);
	 }
	 if (moving) {
	 }
 }

 bool MyRoad::check_removing() {
	 // check its position_y.
	 if (pos.z > 600) {
		 for (int i = 0; i < 2; ++i)
			remove_truck(i);
		 return true;
	 }
	 // if it out off the screen, request removing to state_class

	 return false;
 }

 void MyRoad::CreateTruck(int idx) {
	 trucks[idx] = new MyTruck(pos, speed);
 }

 void MyRoad::remove_truck(int i) {
	 // 1. delete
	 delete trucks[i];
	 std::cout << "삭제 : "<< pos.z << std::endl;
	 // 2. create
	 if (pos.z <= 600) {
		 trucks[i] = new MyTruck(pos, speed);
		 std::cout <<"생성: "<< pos.z << std::endl;
	}
 }

 MyRoad::~MyRoad() {};
