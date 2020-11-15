#pragma once
#include"shader.h"
#include "loadObj.h"
class Scene
{
protected:
	// camera
	glm::mat4 projection;
	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::mat4 view;
	
	glm::vec2 m_screenSize;

	// next scene
public:
	bool m_changeToNextScene;
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void SetScreenSize(glm::vec2 size);
	virtual glm::vec2 GetScreenSize();

	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
	virtual void Init() = 0;
	virtual void Keyboard(unsigned char key) = 0;
};

