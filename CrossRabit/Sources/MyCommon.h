#pragma once
#include "MyState.h"
#include "Mytree.h"
class MyCommon : public MyState
{
private:
	MyTree* trees[3];
	const char* obj_path = "Resources/common.obj";

public:
	MyCommon();
	void draw(glm::mat4 projection, glm::mat4 view, Shader shader);
	void move();
	bool check_removing();
	void CreateTree(int idx);
	void remove_tree(int i);
	~MyCommon();
	float get_obs_speed(int idx) { return 0; };
};

