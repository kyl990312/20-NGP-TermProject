#pragma once
#include "MyHeader.h"
#include "loadOBJ.h"

class MyState
{
public:
	// if character move, map move, this varibles check that map is moving
	bool moving;
	// map move each frame, per this degree
	float moving_degree;
	MyPos collision_pos[3];
	int obs_cnt;
	int tag = -1;
	glm::vec3 obsRotation[3] = {
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};
	glm::vec3 obsSize[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f}
	};;
	int obsTags[3] = {-1,-1,-1};

public:
	// current state's position
	MyPos pos;
	MyState() {}
	virtual void draw(glm::mat4 projection, glm::mat4 view, Shader shader) = 0;
	virtual void move() = 0;
	virtual	bool check_removing() = 0;
	virtual ~MyState() {}
	virtual float get_obs_speed(int idx) = 0;
};

