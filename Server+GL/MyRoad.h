#pragma once
#include "MyState.h"
#include "MyTruck.h"
class MyRoad : public MyState
{
private:
	MyTruck* trucks[2];
	float speed = rand() % 18 + 10;
public:
	MyRoad();
	void move();
	bool check_removing();
	void CreateTruck(int idx);
	void remove_truck(int i);
	~MyRoad();
	float get_obs_speed(int idx) { return 0; };
};

