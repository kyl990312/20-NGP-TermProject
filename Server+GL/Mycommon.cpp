#include "MyCommon.h"

MyCommon::MyCommon() {
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
	obsSize[0] = { 1.f,trees[0]->size,1.f };
	obsSize[0] = { 1.f,trees[1]->size,1.f };
	obsSize[0] = { 1.f,trees[2]->size,1.f };
	obsTags[0] = 19;
	obsTags[1] = 19;
	obsTags[2] = 19;
	obs_cnt = 3;
	tag = 2;

}


void MyCommon::move() {
}

bool MyCommon::check_removing() {

	// check its position_y.
	// if it out off the screen, request removing to state_class
	if (pos.z > 600) {
		return true;
	}
	return false;
}

void MyCommon::CreateTree(int idx) {
	trees[idx] = new MyTree(pos);
}

void MyCommon::remove_tree(int i) {
	if(trees[i] != NULL)
		delete trees[i];
}

MyCommon::~MyCommon() { 
	for (int i = 0; i < obs_cnt; ++i) {
		if (trees[i] != NULL)
			delete trees[i];
	}
};
