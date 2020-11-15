#pragma once
#include "loadObj.h"
#include "Global.h"
enum class HeroState {
	Idle,
	Jump,
	Float,
	Die
};

enum MapState {
	river = 1,
	common,
	trail,
	road
};

class Hero
{
private:

	glm::vec3 m_position;
	const float m_size = 40.0f;
	
	float m_lookAngle;
	const float m_velocityZ = float(5/3);
	float m_frame;
	float m_elapsedTime;

	BoundingBox m_boundingBox;
	glm::vec2 m_deadSinValue;
public:
	float curMapPositionZ;
	float logVelocityX;

	HeroState m_state;
public:
	Hero() { Init(); }
	~Hero() {}


	void Init();
	void Update(float elapsedTime, int tag, glm::vec3* obsPosition, int obsCnt);
	void Render(glm::mat4 projection, glm::mat4 view);
	bool checkCollistion(glm::vec3 obsPosition, int obsTag);

	void Jump(int tag, glm::vec3* obs_pos, int obs_cnt1);
	void Float();
	void Die();

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);
};

