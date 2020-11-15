#include "Scene.h"

void Scene::SetScreenSize(glm::vec2 size)
{
	m_screenSize.x = size.x;
	m_screenSize.y = size.y;
}

glm::vec2 Scene::GetScreenSize()
{
	return m_screenSize;
}
