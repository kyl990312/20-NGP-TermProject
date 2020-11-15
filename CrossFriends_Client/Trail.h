#pragma once
#include "MapLine.h"
#include"Train.h"

class Trail : public MapLine
{
private:
	Train* m_trains[3];

public:
	Trail();
	~Trail();
	virtual void Render(glm::mat4 projection, glm::mat4 view);
	virtual void Update(float elapsedTime);

	void CreateTrain(int idx);
	void RemoveTrain(int idx);

	void TrainWarning(glm::mat4 projection, glm::mat4 view);
};

