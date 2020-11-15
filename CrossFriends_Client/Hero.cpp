#include "Hero.h"

extern loadOBJ models[MAX_MODELS];
extern Shader* shader;

void Hero::Init()
{
	m_position = { 0.0f,0.0f,0.0f };

	m_lookAngle = 0.0f;
	m_frame = 0.0f;

	m_boundingBox = { 0.0f,0.f,0.f,0.f,0.f,0.f };
	m_deadSinValue = { 0.f,0.f };

	m_elapsedTime = 0.f;
	curMapPositionZ = 0.0f;
	logVelocityX = 0.0f;

	m_state = HeroState::Idle;
}

void Hero::Update(float elapsedTime, int tag, glm::vec3* obsPosition, int obsCnt)
{
	m_elapsedTime = elapsedTime;
	if (m_state != HeroState::Die)
		// move backward following map
		m_position.z += SPEED * m_elapsedTime;

	glm::vec3 hero_view_pos = { m_position.x * cos(glm::radians(10.0f)) - m_position.z * sin(glm::radians(10.0f)),0.0f,m_position.x * sin(glm::radians(10.0f)) + m_position.z * cos(glm::radians(10.0f)) };

	switch (m_state)
	{
	case HeroState::Idle:
		std::cout << "Idle" << std::endl;
		// Check hero included in screen range			
		// screen out
		if (hero_view_pos.z > 550 || hero_view_pos.x < -400 || hero_view_pos.x > 400) {
			m_state = HeroState::Die;
		}

		// check collision
		if (tag == MapState::road || tag == MapState::trail) {
			for (int i = 0; i < obsCnt; i++) {
				if (checkCollistion(obsPosition[i], tag)) {
					m_state = HeroState::Die;
				}
			}
		}
		break;
	case HeroState::Jump:
		Jump(tag, obsPosition, obsCnt);
		break;
	case HeroState::Float:
		Float();
		break;
	case HeroState::Die:
		std::cout << "Die" << std::endl;
		Die();
		break;
	}
}

void Hero::Render(glm::mat4 projection, glm::mat4 view)
{
	glm::mat4 model;

	shader->use();
	if (m_state == HeroState::Die) {
		models[ModelsIdx::ghost].load(projection, view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(m_deadSinValue.x + m_position.x, m_deadSinValue.y + m_position.y, m_position.z));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		models[ModelsIdx::ghost].setTransform(model);

		models[ModelsIdx::ghost].draw();
		return;
	}

	models[0].load(projection, view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(m_position.x, m_position.y, m_position.z));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-m_lookAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	models[0].setTransform(model);

	models[0].draw();

}

bool Hero::checkCollistion(glm::vec3 obsPosition, int obsTag)
{
	// make obs_bounding_box
	BoundingBox obs_bounding_box = {
		obsPosition.x + 20,20.0f,25.0f,
		obsPosition.x - 20,-20.0f,-25.0f
	};

	if (obsTag == 3) {
		obs_bounding_box = {
		obsPosition.x + 400,25.0f,25.0f,
		obsPosition.x - 400,-25.0f,-25.0f
		};
	}

	// change my_bounding_box
	m_boundingBox = {
		m_position.x + m_size / 2,m_position.y + m_size / 2,m_position.z + m_size / 2,
		m_position.x - m_size / 2,m_position.y - m_size / 2,m_position.z - m_size / 2
	};

	// aabb - aabb collision checking
	if (m_boundingBox.maxX < obs_bounding_box.minX)
		return false;

	if (m_boundingBox.minX > obs_bounding_box.maxX)
		return false;

	if (m_boundingBox.maxY < obs_bounding_box.minY)
		return false;
	if (m_boundingBox.minY > obs_bounding_box.maxY)
		return false;
	return true;
}

void Hero::Jump(int tag, glm::vec3* obsPos, int obsCnt)
{
	std::cout << "JUMP" << std::endl;
	// Jump
	switch ((int)m_lookAngle) {
	case 0:
		// directon == front
		m_position.z -= 10;
		break;
	case 90:
		// direction == right
		m_position.x += 10;
		break;
	case -90:
		// direction == left
		m_position.x -= 10;
		break;
	}
	// hero is jumping : frame : 5 , height : 30
	m_frame += 1.f;		// 0 ~ 5
	// 0 ~ 30  : 20, 30, 30, 20, 0
	m_position.y = -float(5/18) * m_frame * (m_frame - 5.f);


	// Check Collsion
	switch (tag) {
	case MapState::river:
		for (int i = 0; i < obsCnt; i++) {
			// if True : Land on Log
			if (checkCollistion(obsPos[i], tag)) {
				m_state = HeroState::Float;
				m_position.z = curMapPositionZ;
				m_position.y = obsPos->y + m_size / 2;
				m_frame = 0;
			}
		}
		break;
	case MapState::common:
		for (int i = 0; i < obsCnt; i++) {
			if (checkCollistion(obsPos[i], tag)) {
				switch ((int)m_lookAngle) {
				case 0:
					m_position.x += 50;
					break;
				case -90:
					m_position.x += 10;
					break;
				case 90:
					m_position.x -= 10;
					break;
				}
			}
		}
		break;
	default:
		for (int i = 0; i < obsCnt; i++) {
			if (checkCollistion(obsPos[i], tag)) {
				m_state = HeroState::Die;
			}
		}
		break;
	}

	// Check where hero Land (except Landing at Log)
	if (m_position.y <= 0) {
		if (tag == MapState::river) {
			m_position.y -= 10;
			if (m_position.y < -50)
				m_state = HeroState::Die;
			return;
		}
		// set hero's positionZ at map's positionZ
		m_position.z = curMapPositionZ;
		m_position.y = 0.f;
		m_state = HeroState::Idle;
		m_frame = 0;
	}
}

void Hero::Float()
{
	std::cout << "Float" << std::endl;
	// move along the log
	m_position.x += logVelocityX * m_elapsedTime;

	// Check hero included in screen range
	glm::vec3 hero_view_pos = { m_position.x * cos(glm::radians(10.0f)) - m_position.z * sin(glm::radians(10.0f)),0.0f,m_position.x * sin(glm::radians(10.0f)) + m_position.z * cos(glm::radians(10.0f)) };
	// screen out
	if (hero_view_pos.z > 550 || hero_view_pos.x < -400 || hero_view_pos.x > 400) {
		m_state = HeroState::Die;
	}
}

void Hero::Die()
{
	m_deadSinValue.y += 5;
	m_deadSinValue.x = 20 * sin(glm::radians(m_deadSinValue.y));
}

glm::vec3 Hero::GetPosition()
{
	return m_position;
}

void Hero::SetPosition(glm::vec3 position)
{
	m_position = position;
}
