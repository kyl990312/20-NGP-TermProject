#include "MapLine.h"

glm::vec3 MapLine::GetPosition()
{
	return m_position;
}

void MapLine::SetPosition(glm::vec3 position)
{
	m_position = position;
}
