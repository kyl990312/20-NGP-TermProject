#pragma once
//������ struct

#pragma pack(1)  
typedef struct MapData {
	float x, y, z; // position
	char tag; // ������Ʈ ����
}MapData;

#pragma pack(1)  
typedef struct HeroData {
	float x, y, z; // position
	float lookatX, lookatY, lookatZ;
	bool alive;
}HeroData;