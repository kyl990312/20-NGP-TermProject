#pragma once
#include "loadObj.h"
#include "MyHeader.h"

class MyTruck
{
public:
	const char* obj_path;
	float speed;
	float size;
	float direction;
public:
	MyPos pos;
	MyTruck(MyPos road_pos, float speed);
	void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader);
	void move(MyPos road_pos);
	bool check_removing();
	~MyTruck();
};

