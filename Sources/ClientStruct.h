#pragma once
//데이터 struct

typedef struct MapData {
	float x, y, z; // position
	char tag; // 오브젝트 종류
}MapData;

typedef struct HeroData {
	float x, y, z; // position
	float lookatX, lookatY, lookatZ;
	bool alive;
}HeroData;