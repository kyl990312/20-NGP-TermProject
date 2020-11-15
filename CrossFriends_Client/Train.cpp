#include "Train.h"

extern loadOBJ models[26];

Train::Train(glm::vec3 position)
{
	// pos init
	m_position = { position.x - 2000.0f,position.y,position.z };
	m_velocityX = rand() % 100 + 150;
	m_sizeX = 50.0f;
}

void Train::Render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader)
{
	models[18].load(projection, view);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(m_position.x, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
	models[18].setTransform(model);

	models[18].draw();
}

bool Train::CheckRemoving()
{
	if (m_position.x > 7000 && m_position.z <= 600)
		return true;
	return false;
}
