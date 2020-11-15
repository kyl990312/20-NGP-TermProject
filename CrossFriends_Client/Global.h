#pragma once
extern enum ModelsIdx {
	hero,
	box,
	num0,
	num1,
	num2,
	num3,
	num4,
	num5,
	num6,
	num7,
	num8,
	num9,
	commonMap,
	roadMap,
	riverMap,
	trailMap,
	carObs,
	truckObs,
	trailObs,
	treeObs,
	logObs,
	snow,
	soulCube,
	titleFont,
	titlePlane,
	ghost
};

#define MAX_MODELS 26
#define MAX_SCENE	3

#define SPEED float(5/30)

struct BoundingBox {
	float maxX,maxY,maxZ,minX,minY,minZ;
};