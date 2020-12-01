#pragma once
#include "MyHeader.h"

class MyLog
{
public:
	MyPos pos;
	float speed;
	float size;
	float direction;
public:
	MyLog(MyPos road_pos, float speed);
	void move(MyPos road_pos);
	bool check_removing();
	~MyLog();
};
