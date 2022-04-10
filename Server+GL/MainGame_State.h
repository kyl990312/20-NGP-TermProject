#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>

#include "MyRoad.h"
#include "MyTruck.h"
#include "MyRiver.h"
#include "MyLog.h"
#include "MyTrail.h"
#include "MyTrain.h"
#include "MyCommon.h"
#include "MyTree.h"
#include "MyHero.h"
#include"DataStruct.h"
#define _CRT_NONSTDC_NO_WARNINGS
#pragma comment(lib, "winmm.lib")

class MainGame_State
{
public:
	int change_timer = 50;
	int next_state = 1;
	int map_count = 23;
	MyState** states = new MyState * [map_count];
	bool timerCheck = false;
	bool start = false;

	//hero
	kyrHero hero[3];
	glm::vec3 cur_state_obs_pos[3][3];
	int cur_state_tag[3];
	int cur_state_obs_cnt[3];
	int cur_state_idx[3] = { 0 };
	int pass_state_cnt = 0;

	
public:
	MainGame_State();
	~MainGame_State();
	void update();
	void keyboard(unsigned char key, int x, int y);
	void init_map();
	void hero_update(int idx);
	void GetMapDatas(ObjectData* mapDatas);
	void GetHeroDatas(HeroData* herodatas);
}; 

