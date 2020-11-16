#pragma once
//데이터 struct

#pragma pack(1)  
typedef struct MapData {
	float x, y, z; // position
	char tag; // 오브젝트 종류
}MapData;

#pragma pack(1)  
typedef struct HeroData {
	float x, y, z; // position
	float lookatX, lookatY, lookatZ;
	bool alive;
}HeroData;