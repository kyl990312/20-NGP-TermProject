#include "GameManager.h"
#include "Global.h"

loadOBJ models[MAX_MODELS];
Shader* shader;
Shader* fontShader;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{
	// delete Scenes
	for (int i = 0; i < MAX_SCENE; ++i) {
		if (m_scenes[i] != NULL)
			delete m_scenes[i];
	}
	if (m_scenes != NULL)
		delete m_scenes;
}

void GameManager::Init()
{
	// Make Scenes
	m_scenes = new Scene* [MAX_SCENE];
	m_scenes[0] = new TitleScene;
	m_scenes[0]->Init();
	m_scenes[1] = new MainScene;
	m_scenes[1]->Init();
	m_scenes[2] = new EndScene;
	m_scenes[2]->Init();
	m_curSceneIdx = 0;

	// Load Shader
	shader = new Shader("shaders/vertexshader.glvs", "shaders/fragmentshader.glfs");
	fontShader = new Shader("shaders/vertexshader.glvs", "shaders/font_fragmentshader.glfs");

	// Set Shader values
	shader->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	shader->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	shader->setVec3("lightPos", glm::vec3(0, 800, 2000));
	fontShader->setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	fontShader->setVec3("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
	fontShader->setVec3("lightPos", glm::vec3(0, 800, 2000));
	fontShader->setVec3("", glm::vec3(0, 800, 2000));

	// Load Moldes
	LoadModels();
}

void GameManager::LoadModels()
{
	// Hero
	models[0] = loadOBJ("Resources/rabit.obj", shader->ID);

	// box
	models[1] = loadOBJ("Resources/box.obj", shader->ID);

	// 숫자
	models[2] = loadOBJ("Resources/number_0.obj", fontShader->ID);
	models[3] = loadOBJ("Resources/number_1.obj", fontShader->ID);
	models[4] = loadOBJ("Resources/number_2.obj", fontShader->ID);
	models[5] = loadOBJ("Resources/number_3.obj", fontShader->ID);
	models[6] = loadOBJ("Resources/number_4.obj", fontShader->ID);
	models[7] = loadOBJ("Resources/number_5.obj", fontShader->ID);
	models[8] = loadOBJ("Resources/number_6.obj", fontShader->ID);
	models[9] = loadOBJ("Resources/number_7.obj", fontShader->ID);
	models[10] = loadOBJ("Resources/number_8.obj", fontShader->ID);
	models[11] = loadOBJ("Resources/number_9.obj", fontShader->ID);

	// State
	models[12] = loadOBJ("Resources/common.obj", shader->ID);
	models[13] = loadOBJ("Resources/road.obj", shader->ID);
	models[14] = loadOBJ("Resources/river.obj", shader->ID);
	models[15] = loadOBJ("Resources/trail.obj", shader->ID);

	// obj in state
	models[16] = loadOBJ("Resources/car.obj", shader->ID);
	models[17] = loadOBJ("Resources/truck.obj", shader->ID);
	models[18] = loadOBJ("Resources/train.obj", shader->ID);
	models[19] = loadOBJ("Resources/tree.obj", shader->ID);
	models[20] = loadOBJ("Resources/log.obj", shader->ID);

	// 기타
	models[21] = loadOBJ("Resources/snow.obj", shader->ID);
	models[22] = loadOBJ("Resources/soul_cube.obj", shader->ID);
	models[23] = loadOBJ("Resources/title_font.obj", fontShader->ID);
	models[24] = loadOBJ("Resources/title_plane.obj", shader->ID);
	models[25] = loadOBJ("Resources/ghost.obj", shader->ID);
}

void GameManager::Update(float elpasedTime)
{	
	m_scenes[m_curSceneIdx]->Update(elpasedTime);
	if (m_scenes[m_curSceneIdx]->m_changeToNextScene)
		m_curSceneIdx = (m_curSceneIdx + 1) % MAX_SCENE;
}


void GameManager::Render()
{
	m_scenes[m_curSceneIdx]->Render();
}

void GameManager::Keyboard(unsigned char key)
{
	m_scenes[m_curSceneIdx]->Keyboard(key);
}
