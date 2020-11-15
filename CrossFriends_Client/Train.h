#pragma once
#include"Obstacle.h"
class Train:public Obstacle
{
public:
	Train() {}
	Train(glm::vec3 position);
	~Train() {}
	virtual void Render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader);
	virtual bool CheckRemoving();
};

