#include "loadObj.h"
#include "MyHeader.h"

class MyTree
{
public:
	MyPos pos;
	const char* obj_path = "Resources/tree.obj";
	float size;
public:
	MyTree(MyPos road_pos);
	void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader);
	void move(MyPos road_pos);
	bool check_removing();
	~MyTree();
};
#pragma once
