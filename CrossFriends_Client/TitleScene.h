#pragma once
#include "Scene.h"
class TitleScene :public Scene
{
private:
	glm::vec3 m_position;
	float m_fontSinAngle;
public:
	TitleScene();
	~TitleScene();

	virtual void Update(float elapsedTime);
	virtual void Render();
	virtual void Init();
	virtual void Keyboard(unsigned char key);
	void DrawRabit();
	void DrawFont();
};

