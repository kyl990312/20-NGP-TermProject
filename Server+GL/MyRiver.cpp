#include "MyRiver.h"


MyRiver::MyRiver() {

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
	obsTags[0] = 20;
	obsTags[1] = 20;
	obsTags[2] = 20;
	moving_degree = 0;
	obs_cnt = 3;
	tag = 1;
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
		return true;
	}
	return false;
}

void MyRiver::CreateLog(int idx) {
	logs[idx] = new MyLog(pos, speed);
}

void MyRiver::remove_log(int i) {
	// 1. delete
	if(logs[i]!= NULL)
		delete logs[i];

	// 2. create
	if (pos.z <= 600)
		logs[i] = new MyLog(pos, speed);
}

MyRiver::~MyRiver() {
	for (int i = 0; i < obs_cnt; ++i) {
		if (logs[i] != NULL)
			delete logs[i];
	}

};


float MyRiver::get_obs_speed(int idx) {
	if(logs[idx] != NULL)
		return logs[idx]->speed;
	return 0;
}