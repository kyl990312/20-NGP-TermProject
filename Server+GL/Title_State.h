#pragma once
#include "MyHeader.h"
#include "DataStruct.h"

#include <math.h>
class Title_State
{
public:
	MyPos obj_pos = { 0.0f,0.0f,0.0f };
	float font_sin_angle = 0.0f;
	int clientCnt = 0;

public:
	void update();
	void TitleDatas(ObjectData[]);
};
