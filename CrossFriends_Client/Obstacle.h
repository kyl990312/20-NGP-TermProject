#pragma once
#include "loadObj.h"
class Obstacle
{
protected:
	glm::vec3 m_position;
	float m_velocityX;
	float m_sizeX;
public:
	Obstacle() {}
	Obstacle(glm::vec3 postion) {}
	virtual ~Obstacle() {}

	virtual void Update(float elapsedTime);
	virtual void Render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader) = 0;
	virtual bool CheckRemoving() = 0;

	glm::vec3 GetPosition();
	float GetVelocityX();
	virtual void SetVelocityX(float velocity);
};

