#pragma once
#include "loadObj.h"
#include "MyHeader.h"
#include <math.h>

struct MyCollisionData {
	MyPos pos;
	bool use = false;
};

class kyrHero
{
public:
	// hero's shader_path
	MyPos current_pos{ 0.0f,0.0f,0.0f };
	float direction_angle = 0.0f;
	MyBoundingBox bounding_box{ size / 2,size / 2,size / 2,-size / 2,-size / 2,-size / 2 };
	float size = 40.0f;
	// jumping values
	bool moving = false;
	float jumping_velocity = 30.0f;
	MyPos soul_pos{ 0.0f,0.0f,400.0f };
	bool soul_moving = false;
	bool arrive_at_floor = false;
	bool on_the_log = false;
	float log_speed = 0;
	bool fall_into_river = false;
	int* cur_state_idx = nullptr;
public:
	bool check_collision(MyPos obs_pos,int obs_tag);
	void move();
	bool check_death(MyPos obs_pos, int obs_tag);
	void update(int tag, MyPos* obs_pos, int obs_cnt1);
	void draw(glm::mat4 projection, glm::mat4 view, Shader shader);
	void soul_move();
	void soul_draw(glm::mat4 projection, glm::mat4 view,Shader shader);
};

