#include "TitleScene.h"
#include"Global.h"

extern loadOBJ models[MAX_MODELS];
extern Shader* shader;
extern Shader* fontShader;

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(float elapsedTime)
{
	m_fontSinAngle = (float)(((int)m_fontSinAngle + 5) % 180);
	m_position.z = 50 * sin(glm::radians(m_fontSinAngle));
}

void TitleScene::Render()
{
	shader->use();
	// lightning
	DrawRabit();

	fontShader->use();
	fontShader->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	fontShader->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	fontShader->setVec3("lightPos", glm::vec3(0, 800, 2000));
	fontShader->setVec3("obj_color", glm::vec3(1.0, 0.6, 0.0));
	DrawFont();
}

void TitleScene::Init()
{
	projection = glm::ortho(-300 * (float)m_screenSize.x / (float)m_screenSize.y, 300 * (float)m_screenSize.x / (float)m_screenSize.y, (float)-400, (float)400, (float)-600, (float)600);
	cameraPos = glm::vec3(8.0f, 45.0f, 40);
	cameraDirection = cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	m_position = { 0.f,0.0f,0.0f };
	m_fontSinAngle = 0.0f;

	m_changeToNextScene = false;
}

void TitleScene::Keyboard(unsigned char key)
{
	switch (key)
	{
	default:
		m_changeToNextScene = true;
		break;
	}
}

void TitleScene::DrawRabit()
{
	models[0].load(projection, view);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	// transform
	translation = glm::translate(translation, glm::vec3(300.0f,m_position.y,m_position.z));
	scaling = glm::scale(scaling, glm::vec3(3.0f, 3.0f, 3.0f));
	model = translation * scaling;
	models[0].setTransform(model);

	models[0].draw();
}

void TitleScene::DrawFont()
{
	models[23].load(projection, view);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	// transform
	translation = glm::translate(translation, m_position);
	scaling = glm::scale(scaling, glm::vec3(1.0f, 1.0f, 1.0f));
	model = scaling * translation;
	models[23].setTransform(model);

	models[23].draw();
}
