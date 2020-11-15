#include "Common.h"
#include "Global.h"

extern loadOBJ models[MAX_MODELS];
extern Shader* shader;

Common::Common()
{
	std::cout << "creating Common..." << std::endl;
	// init pos
	// only its z_pos will change in MyCommon()
	m_position = { 0.0f,0.0f,0.0f };

	// init trees
	for (int i = 0; i < 3; ++i) {
		CreateTree(i);
	}
	// let's once make only 1 truck

	// init remaining variables
	moving = false;
	// please change
	// you have to change this value when you start map scrolling
	m_VelocityZ = SPEED;
	collisionPosition[0] = m_trees[0]->GetPosition();
	collisionPosition[1] = m_trees[1]->GetPosition();
	collisionPosition[2] = m_trees[2]->GetPosition();

	m_obsCnt = 3;
	m_tag = 2;
	std::cout << "complete creating Common!" << std::endl;
}

Common::~Common()
{
	for (int i = 0; i < 3; ++i)
		RemoveTree(i);
}

void Common::Render(glm::mat4 projection, glm::mat4 view)
{
	shader->use();
	models[12].load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(m_position.x, m_position.y, m_position.z));

	models[12].setTransform(model);

	models[12].draw();
	for (int i = 0; i < 3; i++)
		m_trees[i]->Render(projection, view, model, *shader);
}

void Common::Update(float elapsedTime)
{
	m_position.z += SPEED * elapsedTime;
}


float Common::GetTreeSpeed(int idx)
{
	return 0.0f;
}

void Common::CreateTree(int idx)
{
	m_trees[idx] = new Tree(m_position);
}

void Common::RemoveTree(int idx)
{
	if(m_trees[idx] != NULL)
		delete m_trees[idx];
}
