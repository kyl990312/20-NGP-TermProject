#pragma once
#include "MyState.h"
#include "MyLog.h"
class MyRiver : public MyState
{
private:
	MyLog* logs[3];
	float speed = rand() % 20 + 10;
public:
	MyRiver();
	void move();
	bool check_removing();
	void CreateLog(int idx);
	void remove_log(int i);
	~MyRiver();
	float get_obs_speed(int idx);
};

