#pragma once
#include "MyHeader.h"
#include <math.h>

enum class HeroState {
	Idle,
	Jump,
	Float,
	Die
};

enum MapState {
	River = 1,
	Common,
	Trail,
	Road
};

class kyrHero
{
public:
	// hero's shader_path
	MyPos current_pos{ 0.0f,0.0f,0.0f };
	float cur_mapState_posZ = 0.f;
	float direction_angle = 0.0f;
	MyBoundingBox bounding_box{ size / 2,size / 2,size / 2,-size / 2,-size / 2,-size / 2 };
	float size = 40.0f;
	// jumping values
	float jump_DeltaX = 0.0f;
	float addedY = 0.0f;
	MyPos soul_pos{ 0.0f,0.0f,400.0f };
	float log_speed = 0;
	//bool fall_into_river = false;
	HeroState _state = HeroState::Idle;
	MyPos prevPosition = { 0.0f,0.0f,0.0f };
	MyPos otherHero[2];

public:
	bool check_collision(MyPos obs_pos,int obs_tag);
	//void jump();
	void Jump(int tag, MyPos* obs_pos, int obs_cnt1);
	void Float();
	void Die();
	//bool check_death(MyPos obs_pos, int obs_tag);
	void update(int tag, MyPos* obs_pos, int obs_cnt1);
	bool CheckCollistionWithHero(MyPos position, float size);

};

