#pragma once
#include "MyHeader.h"

class MyTrain
{
public:
	glm::vec3 pos;
	float speed;
	float size;
	float direction;
public:
	MyTrain(glm::vec3 road_pos);
	void move(glm::vec3 road_pos);
	bool check_removing();
	~MyTrain();
};

