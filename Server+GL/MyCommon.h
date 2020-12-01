#pragma once
#include "MyState.h"
#include "Mytree.h"
class MyCommon : public MyState
{
private:
	MyTree* trees[3];

public:
	MyCommon();
	void move();
	bool check_removing();
	void CreateTree(int idx);
	void remove_tree(int i);
	~MyCommon();
	float get_obs_speed(int idx) { return 0; };
};

