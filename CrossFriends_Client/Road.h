#pragma once
#include "MapLine.h"
#include "Truck.h"
class Road : public MapLine
{
private:
	Truck* m_trucks[3];

public:
	Road();
	~Road();
	virtual void Render(glm::mat4 projection, glm::mat4 view);
	virtual void Update(float elapsedTime);

	void CreateTruck(int idx);
	void RemoveTruck(int idx);
};

