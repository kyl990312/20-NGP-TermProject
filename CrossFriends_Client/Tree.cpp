#include "Tree.h"
#include"Global.h"
extern loadOBJ models[MAX_MODELS];	

Tree::Tree(glm::vec3 position)
{
	// pos init
	m_position = { (float)((rand() % 24 - 12) * 50),position.y,position.z };
	m_sizeX = (float)(rand() % 2 + 1);
	m_velocityX = 0.f;
}

void Tree::Render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader)
{
	models[ModelsIdx::treeObs].load(projection, view);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(m_position.x, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, m_sizeX, 1.0f));
	models[ModelsIdx::treeObs].setTransform(model);

	models[ModelsIdx::treeObs].draw();
}

bool Tree::CheckRemoving()
{
	return false;
}
