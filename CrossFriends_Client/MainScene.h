#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>

#include "Scene.h"
#include "Common.h"
#include "Trail.h"
#include "River.h"
#include "Road.h"
#include "Hero.h"

#define _CRT_NONSTDC_NO_WARNINGS
#pragma comment(lib, "winmm.lib")

class MainScene : public Scene
{
private:
	int map_count = 23;
	MapLine** states = new MapLine * [map_count];
	bool start = false;

	//hero
	Hero hero;
	glm::vec3 cur_state_obs_pos[3];
	glm::vec3 next_state_obs_pos[3];
	int cur_state_tag;
	int next_state_tag;
	int cur_state_obs_cnt;
	int next_state_obs_cnt;
	int cur_state_idx = 0;
	int pass_state_cnt = 0;

	bool back_music = true;
	int change_timer = 50;
public:
	MainScene();
	~MainScene();

	virtual void Update(float elapsedTime);
	virtual void Render();
	virtual void Init();
	virtual void Keyboard(unsigned char key);
	
	void InitMap();
	void DeleteMap();
};

