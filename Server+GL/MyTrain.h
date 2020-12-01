#pragma once
#include "MyHeader.h"

class MyTrain
{
public:
	MyPos pos;
	float speed;
	float size;
	float direction;
public:
	MyTrain(MyPos road_pos);
	void move(MyPos road_pos);
	bool check_removing();
	~MyTrain();
};

