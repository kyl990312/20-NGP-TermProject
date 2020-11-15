#include "Log.h"
#include"Global.h"

extern loadOBJ models[MAX_MODELS];

Log::Log(glm::vec3 position)
{
	m_position = { position.x - 500 - (rand() % 7) * 110, position.y, position.z };
	m_sizeX = 50.0f;
}

void Log::Render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader)
{
	models[ModelsIdx::logObs].load(projection, view);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(m_position.x, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));

	models[ModelsIdx::logObs].setTransform(model);

	models[ModelsIdx::logObs].draw();
}

bool Log::CheckRemoving()
{
	if (m_position.x > 450 && m_position.z <= 600)
		return true;
	return false;
}


