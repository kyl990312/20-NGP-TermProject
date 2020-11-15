#pragma once
#include "MapLine.h"
#include "Tree.h"
class Common : public MapLine
{
private:
	Tree* m_trees[3];
public:
	Common();
	~Common();

	virtual void Render(glm::mat4 projection, glm::mat4 view);
	  virtual void Update(float elapsedTime);
	  virtual float GetTreeSpeed(int idx);

	  void CreateTree(int idx);
	  void RemoveTree(int idx);
};

