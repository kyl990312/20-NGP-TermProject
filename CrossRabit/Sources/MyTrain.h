#pragma once
#include "loadObj.h"
#include "MyHeader.h"

class MyTrain
{
public:
	const char* obj_path = "Resources/train.obj";
	MyPos pos;
	float speed;
	float size;
	float direction;
public:
	MyTrain(MyPos road_pos);
	void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader);
	void move(MyPos road_pos);
	bool check_removing();
	~MyTrain();
};

