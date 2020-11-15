#include "River.h"
#include "Global.h"

extern loadOBJ models[MAX_MODELS];
extern Shader* shader;

void River::Render(glm::mat4 projection, glm::mat4 view)
{
	shader->use();
	models[ModelsIdx::riverMap].load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(m_position.x, m_position.y, m_position.z));

	models[ModelsIdx::riverMap].setTransform(model);

	models[ModelsIdx::riverMap].draw();
	for (int i = 0; i < 3; i++)
		m_logs[i]->Render(projection, view, model, *shader);
}

void River::Update(float elapsedTime)
{
	for (int i = 0; i < 3; ++i) {
		m_logs[i]->Update(elapsedTime);
		collisionPosition[i] = m_logs[i]->GetPosition();
		if (m_logs[i]->CheckRemoving())
			RemoveLog(i);
	}
}

void River::CreateLog(int idx)
{
	m_logs[idx] = new Log(m_position);
}

void River::RemoveLog(int idx)
{
	if (m_logs[idx] != NULL)
		delete m_logs[idx];
}

float River::GetVelocity()
{
	return m_logs[0]->GetVelocityX();
}
