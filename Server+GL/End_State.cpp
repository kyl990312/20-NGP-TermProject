#include "End_State.h"
#include<vector>

End_State::End_State() {}

End_State::~End_State() {}


void End_State::update() {
	std::vector<int> rank;
	rank.reserve(50);
	std::ifstream in("rank.txt");

	int n = 0;
	while (!in.eof()) {
		in >> n;
		rank.push_back(n);
	}

	sort(begin(rank), end(rank), [](const int& a, const int& b) {
		return a > b;
		});

	best_score = rank[0];
	mid_score = rank[1];
	last_score = rank[2];

	rank.clear();
}


void End_State::draw_score(int score) {
	num[2] = score / 100;
	num[1] = (score - num[2] * 100) / 10;
	num[0] = score - num[2] * 100 - num[1] * 10;

	tag[0] = first_number();		// 백의 자리
	tag[1] = second_number();		// 십의 자리
	tag[2] = third_number();		// 일의 자리
}

int End_State::first_number()
{
	int tag;

	switch (num[2]) {
	case 0:
		tag = Num0;
		break;
	case 1:
		tag = Num1;
		break;
	case 2:
		tag = Num2;
		break;
	case 3:
		tag = Num3;
		break;
	case 4:
		tag = Num4;
		break;
	case 5:
		tag = Num5;
		break;
	case 6:
		tag = Num6;
		break;
	case 7:
		tag = Num7;
		break;
	case 8:
		tag = Num8;
		break;
	case 9:
		tag = Num9;
		break;
	default:
		tag = Num0;
		break;
	}

	return tag;
}

int End_State::second_number()
{
	int tag;

	switch (num[1]) {
	case 0:
		tag = Num0;
		break;
	case 1:
		tag = Num1;
		break;
	case 2:
		tag = Num2;
		break;
	case 3:
		tag = Num3;
		break;
	case 4:
		tag = Num4;
		break;
	case 5:
		tag = Num5;
		break;
	case 6:
		tag = Num6;
		break;
	case 7:
		tag = Num7;
		break;
	case 8:
		tag = Num8;
		break;
	case 9:
		tag = Num9;
		break;
	default:
		tag = Num0;
		break;
	}
	return tag;
}

int End_State::third_number()
{
	int tag;
	//shader1->use();

	switch (num[0]) {
	case 0:
		tag = Num0;
		break;
	case 1:
		tag = Num1;
		break;
	case 2:
		tag = Num2;
		break;
	case 3:
		tag = Num3;
		break;
	case 4:
		tag = Num4;
		break;
	case 5:
		tag = Num5;
		break;
	case 6:
		tag = Num6;
		break;
	case 7:
		tag = Num7;
		break;
	case 8:
		tag = Num8;
		break;
	case 9:
		tag = Num9;
		break;
	default:
		tag = Num0;
		break;
	}
	return tag;
}


void End_State::rankingData(ObjectData mapdatas[])
{
	
	for (int i = 0; i < 100; ++i) {
		mapdatas[i].tag = -1;
	}

	ObjectData tmpMap;

	draw_score(best_score);		//400
	tmpMap.tag = tag[0];
	tmpMap.positionX = -200.f;
	tmpMap.positionY = 100.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 2.0f;
	tmpMap.sizeY = 2.0f;
	tmpMap.sizeZ = 2.0f;
	mapdatas[0] = tmpMap;

	tmpMap.tag = tag[1];
	tmpMap.positionX = 0.f;
	tmpMap.positionY = 100.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 2.0f;
	tmpMap.sizeY = 2.0f;
	tmpMap.sizeZ = 2.0f;
	mapdatas[1] = tmpMap;

	tmpMap.tag = tag[2];
	tmpMap.positionX = 200.f;
	tmpMap.positionY = 100.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 2.0f;
	tmpMap.sizeY = 2.0f;
	tmpMap.sizeZ = 2.0f;
	mapdatas[2] = tmpMap;

	draw_score(mid_score);		//400
	tmpMap.tag = tag[0];
	tmpMap.positionX = -200.f;
	tmpMap.positionY = -100.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 2.0f;
	tmpMap.sizeY = 2.0f;
	tmpMap.sizeZ = 2.0f;
	mapdatas[3] = tmpMap;

	tmpMap.tag = tag[1];
	tmpMap.positionX = 0.f;
	tmpMap.positionY = -100.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 2.0f;
	tmpMap.sizeY = 2.0f;
	tmpMap.sizeZ = 2.0f;
	mapdatas[4] = tmpMap;

	tmpMap.tag = tag[2];
	tmpMap.positionX = 200.f;
	tmpMap.positionY = -100.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 2.0f;
	tmpMap.sizeY = 2.0f;
	tmpMap.sizeZ = 2.0f;
	mapdatas[5] = tmpMap;

	draw_score(last_score);		//400
	tmpMap.tag = tag[0];
	tmpMap.positionX = -200.f;
	tmpMap.positionY = -300.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 2.0f;
	tmpMap.sizeY = 2.0f;
	tmpMap.sizeZ = 2.0f;
	mapdatas[6] = tmpMap;

	tmpMap.tag = tag[1];
	tmpMap.positionX = 0.f;
	tmpMap.positionY = -300.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 2.0f;
	tmpMap.sizeY = 2.0f;
	tmpMap.sizeZ = 2.0f;
	mapdatas[7] = tmpMap;

	tmpMap.tag = tag[2];
	tmpMap.positionX = 200.f;
	tmpMap.positionY = -300.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 2.0f;
	tmpMap.sizeY = 2.0f;
	tmpMap.sizeZ = 2.0f;
	mapdatas[8] = tmpMap;
}