#pragma once
#include "MyState.h"
#include "MyTruck.h"
class MyRoad : public MyState
{
private:
	MyTruck* trucks[2];
	const char* obj_path = "Resources/road.obj";
	float speed = rand() % 18 + 10;
public:
	MyRoad();
	void draw(glm::mat4 projection, glm::mat4 view, Shader shader);
	void move();
	bool check_removing();
	void CreateTruck(int idx);
	void remove_truck(int i);
	~MyRoad();
	float get_obs_speed(int idx) { return 0; };
};

