#include "Road.h"
#include"Global.h"

extern loadOBJ models[MAX_MODELS];
extern Shader* shader;

Road::Road()
{
	std::cout << "creating Road..." << std::endl;

	m_position = { 0.0f,0.0f,0.0f };

	// init trucks
	for (int i = 0; i < 2; ++i) {
		CreateTruck(i);
	}

	// init remaining variables
	moving = false;
	m_tag = 4;
	// please changeg
	m_VelocityZ = 0;
	collisionPosition[0] = m_trucks[0]->GetPosition();
	collisionPosition[1] = m_trucks[0]->GetPosition();
	m_obsCnt = 2;
	std::cout << "complete creating road!" << std::endl;
}

Road::~Road()
{
	for (int i = 0; i > m_obsCnt; ++i) {
		RemoveTruck(i);
	}
}

void Road::Render(glm::mat4 projection, glm::mat4 view)
{
	shader->use();
	models[ModelsIdx::roadMap].load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(m_position.x, m_position.y, m_position.z));
	models[ModelsIdx::roadMap].setTransform(model);

	models[ModelsIdx::roadMap].draw();
	for (int i = 0; i < 2; ++i)
		m_trucks[i]->Render(projection, view, model,*shader);
}

void Road::Update(float elapsedTime)
{
	for (int i = 0; i < 2; ++i) {
		m_trucks[i]->Update(elapsedTime);
		collisionPosition[i] = m_trucks[i]->GetPosition();
		if (m_trucks[i]->CheckRemoving())
			RemoveTruck(i);
	}
}


void Road::CreateTruck(int idx)
{
	m_trucks[idx] = new Truck(m_position);
}

void Road::RemoveTruck(int idx)
{
	if (m_trucks[idx] != NULL)
		delete m_trucks[idx];
}
