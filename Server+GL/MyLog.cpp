#include "MyLog.h"

extern float elapsedTimeSec;

MyLog::MyLog(MyPos road_pos, float speed_state) {
	// pos init
	pos = { road_pos.x - 500 - (rand() % 7)* 110, road_pos.y, road_pos.z };
	speed = speed_state;
	size = 50.0f;
	direction = 1;
}

void MyLog::move(MyPos road_pos) {
	pos.x += speed * elapsedTimeSec * direction * SPEED;
}

bool MyLog::check_removing() {
	if (pos.x > 450 && pos.z <= 600)
		return true;
	return false;
}

MyLog::~MyLog() {  };