#pragma once
struct Vec3 {
	float x, y, z;
};
class GameObject
{
private:
	Vec3 position;
	Vec3 velocity;
public:
	virtual void Update(float elapsedTime);
	virtual void Render();
};

