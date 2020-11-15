#pragma once
#include"MapLine.h"
#include "Log.h"

class River:public MapLine
{
private:
	Log* m_logs[3];

public:
	virtual void Render(glm::mat4 projection, glm::mat4 view);
	virtual void Update(float elapsedTime);

	void CreateLog(int idx);
	void RemoveLog(int idx);
	float GetVelocity();
};

