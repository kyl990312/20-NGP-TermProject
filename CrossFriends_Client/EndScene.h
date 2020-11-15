#pragma once
#include "Scene.h"
class EndScene : public Scene
{
public:
	virtual void Update(float elapsedTime);
	virtual void Render();
	virtual void Init();
	virtual void Keyboard(unsigned char key);
};

