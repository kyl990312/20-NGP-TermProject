#include "Obstacle.h"

void Obstacle::Update(float elapsedTime)
{
	m_position.x += m_velocityX * elapsedTime;
}

glm::vec3 Obstacle::GetPosition()
{
	return m_position;
}

float Obstacle::GetVelocityX()
{
	return m_velocityX;
}

void Obstacle::SetVelocityX(float velocity)
{
	m_velocityX = velocity;
}
