#include "Truck.h"
#include "Global.h"

extern loadOBJ models[MAX_MODELS];

Truck::Truck(glm::vec3 position)
{
	// pos init
	m_position = { position.x - 500 - (rand() % 8) * 110,position.y,position.z };
	m_sizeX = 50.0f;
}

void Truck::Render(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader)
{
	// change road's positoin 
	model = glm::translate(model, glm::vec3(m_position.x, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
	models[m_modelIdx].setTransform(model);

	models[m_modelIdx].draw();
}

bool Truck::CheckRemoving()
{
	// request removing to road class
	if (m_position.x > 450 && m_position.z <= 600)
		return true;

	return false;
}

void Truck::SetVelocityX(float speed)
{
	m_velocityX = speed;

	if (speed < 20)
		m_modelIdx = ModelsIdx::truckObs;
	else
		m_modelIdx = ModelsIdx::carObs;
}
