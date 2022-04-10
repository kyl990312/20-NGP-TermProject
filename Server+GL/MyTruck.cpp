#include "MyTruck.h"

extern float elapsedTimeSec;

MyTruck::MyTruck(glm::vec3 road_pos, float state_speed) {
	// pos init
	pos = { road_pos.x - 500 - (rand() % 8) * 110,road_pos.y,road_pos.z };
	speed = state_speed;
	size = 50.0f; 
	direction = 1;
	if (speed < 20) {
		tag = 17;
	}
	else {
		tag = 16;
	}
}

void MyTruck::move(glm::vec3 road_pos) {
	pos.x += speed * elapsedTimeSec *direction * SPEED;
}

bool MyTruck::check_removing() {
	// request removing to road class
	if (pos.x > 450 && pos.z <= 600)
		return true;

	return false;
}

MyTruck::~MyTruck() {  }

