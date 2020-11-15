#pragma once
#include "loadObj.h"
class MapLine
{
protected:
	// map move each frame, per this degree
	float m_VelocityZ;
	glm::vec3 m_position;

public:
	int m_tag;  
	int m_obsCnt;
	bool moving;
	glm::vec3 collisionPosition[3];

	// current state's position
	MapLine() {}
	virtual ~MapLine() {}

	virtual void Render(glm::mat4 projection, glm::mat4 view) = 0;
	virtual void Update(float elapsedTime) = 0;
	virtual	bool CheckRemoving() {	
		if (m_position.z > 600) {

			return true;
		}
		return false;
	};

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);
};

