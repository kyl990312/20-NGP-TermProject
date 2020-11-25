#pragma once
#pragma once
#include "MyState.h"
class FirstState : public MyState
{
private:
	const char* obj_path = "Resources/common.obj";

public:
	FirstState();
	void draw(glm::mat4 projection, glm::mat4 view, Shader shader);
	void move();
	bool check_removing();
	~FirstState();
	float get_obs_speed(int idx) { return 0; };
};



