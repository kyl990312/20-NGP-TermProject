#pragma once
#include "MyHeader.h"

class MyTruck
{
public:
	float speed;
	float size;
	float direction;
	int tag;
public:
	glm::vec3 pos;
	MyTruck(glm::vec3 road_pos, float speed);
	void move(glm::vec3 road_pos);
	bool check_removing();
	~MyTruck();
};

