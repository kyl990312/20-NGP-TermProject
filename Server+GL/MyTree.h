#include "MyHeader.h"

class MyTree
{
public:
	glm::vec3 pos;
	float size;
public:
	MyTree(glm::vec3 road_pos);
	void move(glm::vec3 road_pos);
	bool check_removing();
	~MyTree();
};
#pragma once
