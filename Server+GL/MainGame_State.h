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
	glm::mat4 projection = glm::ortho(-300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, 300 * (float)SCR_WIDTH / (float)SCR_HEIGHT, (float)-400, (float)400, (float)-600, (float)600);
	glm::vec3 cameraPos = glm::vec3(8.0f, 45.0f, 40);
	glm::vec3 cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	int map_count = 23;
	MyState** states = new MyState * [map_count];
	bool timerCheck = false;
	bool start = false;
	Shader* shader =  new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");

	//hero
	Shader* hero_shader = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");
	kyrHero hero[3];
	MyPos cur_state_obs_pos[3][3];
	int cur_state_tag[3];
	int cur_state_obs_cnt[3];
	int cur_state_idx[3] = { 0 };
	int pass_state_cnt = 0;

	bool back_music = true;
	
public:
	MainGame_State();
	~MainGame_State();
	void Display();
	void update();
	void init_map();
	void keyboard(unsigned char key, int x, int y);
	void hero_update(int idx);
	void GetMapDatas(ObjectData* mapDatas);
	void GetHeroDatas(HeroData* herodatas);
	void Init();
	void DeleteAll();
}; 

