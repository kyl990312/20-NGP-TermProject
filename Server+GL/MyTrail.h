#pragma once
#include "MyState.h"
#include "MyTrain.h"
class MyTrail : public MyState
{
private:
	MyTrain* trains[1];


public:
	MyTrail();
	void move();
	bool check_removing();
	void CreateTrain(int idx);
	void remove_train(int i);
	~MyTrail();
	float get_obs_speed(int idx) { return 0; };

};
