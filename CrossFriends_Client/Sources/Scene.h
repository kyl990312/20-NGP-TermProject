#pragma once
class Scene
{
private:

public:
	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
	virtual void Init() = 0;
};

