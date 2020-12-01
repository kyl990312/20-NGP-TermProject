#include "MyTrain.h"

extern float elapsedTimeSec;

MyTrain::MyTrain(MyPos road_pos) {
	// pos init
	pos = { road_pos.x - 2000.0f,road_pos.y,road_pos.z };
	speed = rand()% 100 + 150;
	size = 50.0f;
	direction = 1;

}

void MyTrain::move(MyPos road_pos) {
	pos.x += speed * elapsedTimeSec * direction * SPEED;
}

bool MyTrain::check_removing() {
	// request removing to road class
	if (pos.x > 7000 && pos.z <= 600)
		return true;
	return false;
}

MyTrain::~MyTrain() {  };