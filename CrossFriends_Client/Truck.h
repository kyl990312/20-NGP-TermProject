#pragma once
#include"loadObj.h"
#include"Obstacle.h"
class Truck : public Obstacle
{
private:
	int m_modelIdx;
public:
	Truck() {}
	Truck(glm::vec3 position);
	~Truck() {}

	void Render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader);
	virtual bool CheckRemoving();

	void SetVelocityX(float speed);
};

