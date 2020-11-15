#pragma once
#include"Obstacle.h"
class Log : public Obstacle
{
public:
	Log() {};
	Log(glm::vec3 position);
	~Log() {}

	virtual void Render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader);
	virtual bool CheckRemoving();

};

