#include "MyHeader.h"

class MyTree
{
public:
	MyPos pos;
	float size;
public:
	MyTree(MyPos road_pos);
	void move(MyPos road_pos);
	bool check_removing();
	~MyTree();
};
#pragma once
