#pragma once
//������ struct

typedef struct MapData {
	float x, y, z; // position
	char tag; // ������Ʈ ����
}MapData;

typedef struct HeroData {
	float x, y, z; // position
	float lookatX, lookatY, lookatZ;
	bool alive;
}HeroData;