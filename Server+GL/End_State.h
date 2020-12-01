#pragma once
#include <list>
#include <fstream>
#include <algorithm>
#include "MyHeader.h"
#include "DataStruct.h"

class End_State
{
public:
	int next_state = 2;

	std::list<int> rank = {};
	int cur_score;
	int best_score;
	int mid_score;
	int last_score;
	int num[3] = { 0, };
	int tag[3];

public:
	End_State();
	~End_State();
	void update();
	void draw_score(int);
	int first_number();
	int second_number();
	int third_number();

	void rankingData(ObjectData[]);
};

