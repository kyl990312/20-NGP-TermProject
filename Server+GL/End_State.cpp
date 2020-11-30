#include "End_State.h"

extern loadOBJ models[26];

End_State::End_State() {
	//std::cout << "enter endstate" << std::endl;
	//std::ifstream in("rank.txt");
	//int num;
	//while (!in.eof()) {
	//	in >> num;
	//	//rank.push_back(num);
	//}
}

End_State::~End_State() {

}

void End_State::Display() {
	shader1->use();
	shader1->setVec3("obj_color", glm::vec3(1.0, 1.0, 0.0));
	draw_score(cur_score);		//400
	draw_score(best_score);		//200
	draw_score(mid_score);		//80
	draw_score(last_score);		//-40
}

void End_State::update() {
	std::vector<int> rank;
	rank.reserve(50);
	std::ifstream in("rank.txt");
	if (!in)
		std::cout << "파일이 안 열림" << std::endl;

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

void End_State::keyboard(unsigned char key, int x, int y) {
	switch (key) {
	default:
		next_state = 0;
		break;
	}
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
	shader1->use();

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

	/*glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	translation = glm::translate(translation, glm::vec3(-100.0f, y_pos, 100.0f));
	model = scaling * translation;
	first.setTransform(model);
	first.draw();*/

}

int End_State::second_number()
{
	int tag;
	shader1->use();

	switch (num[1]) {
		/*case 0:
			second = models[2];
			second.load(projection, view);
			break;
		case 1:
			second = models[3];
			second.load(projection, view);
			break;
		case 2:
			second = models[3];
			second.load(projection, view);
			break;
		case 3:
			second = models[4];
			second.load(projection, view);
			break;
		case 4:
			second = models[5];
			second.load(projection, view);
			break;
		case 5:
			second = models[6];
			second.load(projection, view);
			break;
		case 6:
			second = models[7];
			second.load(projection, view);
			break;
		case 7:
			second = models[8];
			second.load(projection, view);
			break;
		case 8:
			second = models[9];
			second.load(projection, view);
			break;
		case 9:
			second = models[10];
			second.load(projection, view);
			break;
		default:
			second = models[2];
			second.load(projection, view);
			break;*/
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

	/*glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	translation = glm::translate(translation, glm::vec3(0.0f, y_pos, 100.0f));
	model = scaling * translation;
	second.setTransform(model);
	second.draw();*/
}

int End_State::third_number()
{
	int tag;
	shader1->use();

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

	/*loadOBJ third;

	shader1->use();

	switch (num[0]) {
	case 0:
		third = models[2];
		third.load(projection, view);
		break;
	case 1:
		third = models[3];
		third.load(projection, view);
		break;
	case 2:
		third = models[3];
		third.load(projection, view);
		break;
	case 3:
		third = models[4];
		third.load(projection, view);
		break;
	case 4:
		third = models[5];
		third.load(projection, view);
		break;
	case 5:
		third = models[6];
		third.load(projection, view);
		break;
	case 6:
		third = models[7];
		third.load(projection, view);
		break;
	case 7:
		third = models[8];
		third.load(projection, view);
		break;
	case 8:
		third = models[9];
		third.load(projection, view);
		break;
	case 9:
		third = models[10];
		third.load(projection, view);
		break;
	default:
		third = models[2];
		third.load(projection, view);
		break;
	}


	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	translation = glm::translate(translation, glm::vec3(100.0f, y_pos, 100.0f));
	model = scaling * translation;
	third.setTransform(model);
	third.draw();*/
}


void End_State::rankingData(ObjectData mapdatas[])
{
	shader1->use();
	//shader1->setVec3("obj_color", glm::vec3(1.0, 1.0, 0.0));
	for (int i = 0; i < 100; ++i) {
		mapdatas[i].tag = -1;
		mapdatas[i].positionX = 0.0f;
		mapdatas[i].positionY = 0.0f;
		mapdatas[i].positionZ = 0.0f;
		mapdatas[i].rotationX = 0.0f;
		mapdatas[i].rotationY = 0.0f;
		mapdatas[i].rotationZ = 0.0f;
		mapdatas[i].sizeX = 0.0f;
		mapdatas[i].sizeY = 0.0f;
		mapdatas[i].sizeZ = 0.0f;
	}

	//draw_score(cur_score);		//400
	//draw_score(best_score);		//200
	//draw_score(mid_score);		//80
	//draw_score(last_score);		//-40



	ObjectData tmpMap;

	draw_score(best_score);		//400
	tmpMap.tag = tag[0];
	tmpMap.positionX = 0.f;
	tmpMap.positionY = 400.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[0] = tmpMap;

	tmpMap.tag = tag[1];
	tmpMap.positionX = 100.f;
	tmpMap.positionY = 400.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[1] = tmpMap;

	tmpMap.tag = tag[2];
	tmpMap.positionX = 200.f;
	tmpMap.positionY = 400.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[2] = tmpMap;

	draw_score(mid_score);		//400
	tmpMap.tag = tag[0];
	tmpMap.positionX = 0.f;
	tmpMap.positionY = 200.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[3] = tmpMap;

	tmpMap.tag = tag[1];
	tmpMap.positionX = 100.f;
	tmpMap.positionY = 200.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[4] = tmpMap;

	tmpMap.tag = tag[2];
	tmpMap.positionX = 200.f;
	tmpMap.positionY = 200.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[5] = tmpMap;

	draw_score(last_score);		//400
	tmpMap.tag = tag[0];
	tmpMap.positionX = 0.f;
	tmpMap.positionY = 0.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[6] = tmpMap;

	tmpMap.tag = tag[1];
	tmpMap.positionX = 100.f;
	tmpMap.positionY = 0.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[7] = tmpMap;

	tmpMap.tag = tag[2];
	tmpMap.positionX = 200.f;
	tmpMap.positionY = 0.f;
	tmpMap.positionZ = 0.f;
	tmpMap.rotationX = 0.0f;
	tmpMap.rotationY = 0.0f;
	tmpMap.rotationZ = 0.0f;
	tmpMap.sizeX = 3.0f;
	tmpMap.sizeY = 3.0f;
	tmpMap.sizeZ = 3.0f;
	mapdatas[8] = tmpMap;
}