#include "MyTrail.h"
#include<iostream>

MyTrail::MyTrail() {

	// init pos
	// only its z_pos will change in MyTrail()
	pos = { 0.0f,0.0f,0.0f };

	// init trains
	CreateTrain(0);

	// init remaining variables
	moving = false;
	// please change
	// you have to change this value when you start map scrolling
	moving_degree = 0;
	moving_degree = 0;
	collision_pos[1] = { -800,-800,-800 };
	collision_pos[2] = { -800,-800,-800 };
	collision_pos[0] = trains[0]->pos;
	obsRotation[0] = {0.0f,90.0f,0.0f};
	obsSize[0] = {1.f,1.f,1.f};
	obsTags[0] = 18;
	obs_cnt = 1;
	tag = 3;

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
	if(trains[i] != NULL)
		delete trains[i];

	// 2. create
	if (pos.z <= 600)
		trains[i] = new MyTrain(pos);
}


MyTrail::~MyTrail() {
	for (int i = 0; i < obs_cnt; ++i) {
		if (trains[i] != NULL)
			delete trains[i];
	}


};
