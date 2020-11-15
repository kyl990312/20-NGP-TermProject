#include "End_State.h"

extern loadOBJ models[26];
extern Shader* fontShader;

End_State::End_State() {
	std::cout << "enter endstate" << std::endl;
	std::ifstream in("rank.txt");
	int num;
	while (!in.eof()) {
		in >> num;
		rank.push_back(num);
	}
	in.close();
}

End_State::~End_State() {

}

void End_State::Display() {
	fontShader->use();
	fontShader->setVec3("obj_color", glm::vec3(1.0, 1.0, 0.0));
	draw_score(400, cur_score);
	draw_score(200, best_score);
	draw_score(80, mid_score);
	draw_score(-40, last_score);
}

void End_State::update() {
	std::cout << "update" << std::endl;
	if (!rank.empty()) {
		rank.reverse();
		std::list<int>::iterator iter = rank.begin();
		cur_score = *iter;
		rank.sort();
		rank.reverse();
		iter = rank.begin();
		best_score = *(iter);
		if (best_score == cur_score) {
			++iter;
			mid_score = *(++iter);
			last_score = *(++iter);

		}
		else if (mid_score == cur_score) {
			mid_score = *(++iter);
			++iter;
			last_score = *(++iter);
		}
		else {
			mid_score = *(++iter);
			last_score = *(++iter);
		}
		rank.clear();
	}
}

void End_State::keyboard(unsigned char key, int x, int y) {
	switch (key) {
	default:
		next_state = 0;
		break;
	}
}

void End_State::draw_score(float y_pos, int score) {

	num[2] = score / 100;
	num[1] = (score - num[2] * 100) / 10;
	num[0] = score - num[2] * 100 - num[1] * 10;

	first_number(y_pos);
	second_number(y_pos);
	third_number(y_pos);
}

void End_State::first_number(float y_pos)
{
	loadOBJ first;
	fontShader->use();

	switch (num[2]) {
	case 0:
		first = models[2];
		first.load(projection, view);
		break;
	case 1:
		first = models[3];
		first.load(projection, view);
		break;
	case 2:
		first = models[3];
		first.load(projection, view);
		break;
	case 3:
		first = models[4];
		first.load(projection, view);
		break;
	case 4:
		first = models[5];
		first.load(projection, view);
		break;
	case 5:
		first = models[6];
		first.load(projection, view);
		break;
	case 6:
		first = models[7];
		first.load(projection, view);
		break;
	case 7:
		first = models[8];
		first.load(projection, view);
		break;
	case 8:
		first = models[9];
		first.load(projection, view);
		break;
	case 9:
		first = models[10];
		first.load(projection, view);
		break;
	default:
		first = models[2];
		first.load(projection, view);
		break;
	}


	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	translation = glm::translate(translation, glm::vec3(-100.0f, y_pos, 100.0f));
	model = scaling * translation;
	first.setTransform(model);
	first.draw();
}


void End_State::second_number(float y_pos)
{
	loadOBJ second;

	fontShader->use();

	switch (num[1]) {
	case 0:
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
		break;
	}

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	translation = glm::translate(translation, glm::vec3(0.0f, y_pos, 100.0f));
	model = scaling * translation;
	second.setTransform(model);
	second.draw();
}


void End_State::third_number(float y_pos)
{
	loadOBJ third;

	fontShader->use();

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
	third.draw();
}
