#include "MyTree.h"

MyTree::MyTree(MyPos road_pos) {
	// pos init
	pos = { (float)((rand() % 24 - 12) * 50),road_pos.y,road_pos.z };
	size = (float)(rand() % 2 + 1);
}

void MyTree::move(MyPos road_pos) {
}

bool MyTree::check_removing() {
	return false;
}

MyTree::~MyTree() {

};