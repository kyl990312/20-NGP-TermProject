#pragma once
#include "MyHeader.h"

class MyLog
{
public:
	glm::vec3 pos;
	float speed;
	float size;
	float direction;
public:
	MyLog(glm::vec3 road_pos, float speed);
	void move(glm::vec3 road_pos);
	bool check_removing();
	~MyLog();
};
