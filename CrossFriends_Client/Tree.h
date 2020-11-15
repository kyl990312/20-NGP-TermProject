#pragma once
#include"Obstacle.h"
class Tree : public Obstacle
{
public:
	Tree(glm::vec3 position);
	~Tree() {}
	
	virtual void Render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader);
	virtual bool CheckRemoving();
};

