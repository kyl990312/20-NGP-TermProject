#pragma once
#include "TitleScene.h"
#include "MainScene.h"
#include "EndScene.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	Scene** m_scenes;
	int m_curSceneIdx;

	void Init();
	void LoadModels();

	void Update(float elpasedTime);
	void Render();
	void Keyboard(unsigned char key);

};

