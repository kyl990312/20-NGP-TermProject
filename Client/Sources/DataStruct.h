#pragma once
//������ struct

#pragma pack(1)  
typedef struct ObjectData {
	float positionX, positionY, positionZ; // position
	float rotationX, rotationY, rotationZ;
	float sizeX, sizeY, sizeZ;
	char tag; // ������Ʈ ����
}ObjectData;

#pragma pack(1)  
typedef struct HeroData {
	float x, y, z; // position
	float rotaionAngle;
	bool alive;
}HeroData;

enum Scene {
	Title,
	MainGame,
	End
};

enum ModelIdx {
	Hero,
	Box,
	Num0, 	Num1,	Num2,	Num3,	Num4,	Num5,Num6,	Num7,	Num8,	Num9,
	Common,	Road, River, Trail,
	Car, Truck, Train, Tree, Log,
	Snow,
	SoulCube,
	TitleFont, TitlePlane,
	Ghost,
	StartButton
};