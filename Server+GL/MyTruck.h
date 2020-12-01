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
	MyPos pos;
	MyTruck(MyPos road_pos, float speed);
	void move(MyPos road_pos);
	bool check_removing();
	~MyTruck();
};

