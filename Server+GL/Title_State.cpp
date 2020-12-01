#include "Title_State.h"

void Title_State::update() {
	font_sin_angle = (float)(((int)font_sin_angle + 5) % 180);
	obj_pos.z = 50 * sin(glm::radians(font_sin_angle));
}


void Title_State::TitleDatas(ObjectData mapdatas[]) {
	for (int i = 0; i < 100; ++i) {
		mapdatas[i].tag = -1;
	}

	ObjectData tmpMap;

	tmpMap.tag = ModelIdx::Hero;
	tmpMap.positionX = 300.0f;
	tmpMap.positionY = 0.f;
	tmpMap.positionZ = obj_pos.z;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[0] = tmpMap;

	tmpMap.tag = ModelIdx::TitleFont;
	tmpMap.positionX = 0.f;
	tmpMap.positionY = 0.f;
	tmpMap.positionZ = obj_pos.z;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 1.0f;
	tmpMap.sizeY = 1.0f;
	tmpMap.sizeZ = 1.0f;
	mapdatas[1] = tmpMap;

	tmpMap.tag = ModelIdx::StartButton;
	tmpMap.positionX = 10.0f;
	tmpMap.positionY = -300.0f;
	tmpMap.positionZ = 10.0f;
	tmpMap.rotationX = 60.0f;
	tmpMap.rotationY = 6.0f;
	tmpMap.rotationZ = -27.0f;
	tmpMap.sizeX = 3.5f;
	tmpMap.sizeY = 4.0f;
	tmpMap.sizeZ = 4.0f;
	mapdatas[2] = tmpMap;
}
