#include "Trail.h"
#include "Global.h"
extern loadOBJ models[26];
extern Shader* shader;


Trail::Trail()
{
	std::cout << "creating Trail..." << std::endl;
	// init pos
	// only its z_pos will change in MyTrail()
	m_position = { 0.0f,0.0f,0.0f };

	// init trains
	CreateTrain(0);
	
	// please change
	// you have to change this value when you start map scrolling
	m_VelocityZ = 0;
	collisionPosition[1] = { -800,-800,-800 };
	collisionPosition[2] = { -800,-800,-800 };
	m_obsCnt = 1;
	m_tag = 3;
	std::cout << "complete creating trail!" << std::endl;
}

Trail::~Trail()
{
	if (m_trains[0] != NULL) {
		delete m_trains[0];
	}
}

void Trail::Render(glm::mat4 projection, glm::mat4 view)
{
	//loadOBJ obj(obj_path, shader.ID);
	shader->use();
	models[ModelsIdx::trailMap].load(projection, view);

	glm::mat4 model = glm::mat4(1.0f);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(m_position.x, m_position.y, m_position.z));
	models[ModelsIdx::trailMap].setTransform(model);

	models[ModelsIdx::trailMap].draw();
	TrainWarning(projection, view);
	m_trains[0]->Render(projection, view, model, *shader);
}

void Trail::Update(float elapsedTime)
{
	m_trains[0]->Update(elapsedTime);
	collisionPosition[0] = m_trains[0]->GetPosition();
	if (m_trains[0]->CheckRemoving())
		RemoveTrain(0);
}

void Trail::CreateTrain(int idx)
{
	m_trains[idx] = new Train(m_position);
}

void Trail::RemoveTrain(int idx)
{
	if (m_trains[idx] != NULL)
		delete m_trains[idx];
}

void Trail::TrainWarning(glm::mat4 projection, glm::mat4 view)
{
	Shader light("shaders/trainwarningvertex.glvs", "shaders/trainwarningfragment.glfs"); // you can name your shader files however you like

	light.use();

	loadOBJ lightbox("Resources/box.obj", light.ID);

	lightbox.load(projection, view);

	//За·Д
	glm::mat4 transMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatix = glm::mat4(1.0f);
	glm::mat4 myTransformeVector = glm::mat4(1.0f);
	glm::vec3 lightColor = glm::vec3(1.0f);

	transMatrix = glm::translate(transMatrix, glm::vec3(0.0f, 0.0f, m_position.z));
	scaleMatix = glm::scale(scaleMatix, glm::vec3(20.0f, 21.0f, 20.0f));

	myTransformeVector = transMatrix * scaleMatix;
	lightbox.setTransform(myTransformeVector);

	if (m_trains[0]->GetPosition().x > -1500)
		lightColor = glm::vec3(1.0f, 0.0f, 0.0f);
	if (m_trains[0]->GetPosition().x > 600)
		lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	light.setVec3("lightColor", lightColor);

	lightbox.draw();
}
