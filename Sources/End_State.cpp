#include "End_State.h"

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
	shader1->use();
	shader1->setVec3("obj_color", glm::vec3(1.0, 1.0, 0.0));
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
	loadOBJ* first = nullptr;
	shader1->use();

	switch (num[2]) {
	case 0:
		first = new loadOBJ("Resources/number_0.obj", shader1->ID);
		first->load(projection, view);
		break;
	case 1:
		first = new loadOBJ("Resources/number_1.obj", shader1->ID);
		first->load(projection, view);
		break;
	case 2:
		first = new loadOBJ("Resources/number_2.obj", shader1->ID);
		first->load(projection, view);
		break;
	case 3:
		first = new loadOBJ("Resources/number_3.obj", shader1->ID);
		first->load(projection, view);
		break;
	case 4:
		first = new loadOBJ("Resources/number_4.obj", shader1->ID);
		first->load(projection, view);
		break;
	case 5:
		first = new loadOBJ("Resources/number_5.obj", shader1->ID);
		first->load(projection, view);
		break;
	case 6:
		first = new loadOBJ("Resources/number_6.obj", shader1->ID);
		first->load(projection, view);
		break;
	case 7:
		first = new loadOBJ("Resources/number_7.obj", shader1->ID);
		first->load(projection, view);
		break;
	case 8:
		first = new loadOBJ("Resources/number_8.obj", shader1->ID);
		first->load(projection, view);
		break;
	case 9:
		first = new loadOBJ("Resources/number_9.obj", shader1->ID);
		first->load(projection, view);
		break;
	default:
		first = new loadOBJ("Resources/number_0.obj", shader1->ID);
		first->load(projection, view);
		break;
	}


	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	translation = glm::translate(translation, glm::vec3(-100.0f, y_pos, 100.0f));
	model = scaling * translation;
	first->setTransform(model);
	first->draw();
	delete first;
}


void End_State::second_number(float y_pos)
{
	loadOBJ* second = nullptr;

	shader1->use();

	switch (num[1]) {
	case 0:
		second = new loadOBJ("Resources/number_0.obj", shader1->ID);
		second->load(projection, view);
		break;
	case 1:
		second = new loadOBJ("Resources/number_1.obj", shader1->ID);
		second->load(projection, view);
		break;
	case 2:
		second = new loadOBJ("Resources/number_2.obj", shader1->ID);
		second->load(projection, view);
		break;
	case 3:
		second = new loadOBJ("Resources/number_3.obj", shader1->ID);
		second->load(projection, view);
		break;
	case 4:
		second = new loadOBJ("Resources/number_4.obj", shader1->ID);
		second->load(projection, view);
		break;
	case 5:
		second = new loadOBJ("Resources/number_5.obj", shader1->ID);
		second->load(projection, view);
		break;
	case 6:
		second = new loadOBJ("Resources/number_6.obj", shader1->ID);
		second->load(projection, view);
		break;
	case 7:
		second = new loadOBJ("Resources/number_7.obj", shader1->ID);
		second->load(projection, view);
		break;
	case 8:
		second = new loadOBJ("Resources/number_8.obj", shader1->ID);
		second->load(projection, view);
		break;
	case 9:
		second = new loadOBJ("Resources/number_9.obj", shader1->ID);
		second->load(projection, view);
		break;
	default:
		second = new loadOBJ("Resources/number_0.obj", shader1->ID);
		second->load(projection, view);
		break;
	}


	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	translation = glm::translate(translation, glm::vec3(0.0f, y_pos, 100.0f));
	model = scaling * translation;
	second->setTransform(model);
	second->draw();
	delete second;

}


void End_State::third_number(float y_pos)
{
	loadOBJ* third = nullptr;

	shader1->use();

	switch (num[0]) {
	case 0:
		third = new loadOBJ("Resources/number_0.obj", shader1->ID);
		third->load(projection, view);
		break;
	case 1:
		third = new loadOBJ("Resources/number_1.obj", shader1->ID);
		third->load(projection, view);
		break;
	case 2:
		third = new loadOBJ("Resources/number_2.obj", shader1->ID);
		third->load(projection, view);
		break;
	case 3:
		third = new loadOBJ("Resources/number_3.obj", shader1->ID);
		third->load(projection, view);
		break;
	case 4:
		third = new loadOBJ("Resources/number_4.obj", shader1->ID);
		third->load(projection, view);
		break;
	case 5:
		third = new loadOBJ("Resources/number_5.obj", shader1->ID);
		third->load(projection, view);
		break;
	case 6:
		third = new loadOBJ("Resources/number_6.obj", shader1->ID);
		third->load(projection, view);
		break;
	case 7:
		third = new loadOBJ("Resources/number_7.obj", shader1->ID);
		third->load(projection, view);
		break;
	case 8:
		third = new loadOBJ("Resources/number_8.obj", shader1->ID);
		third->load(projection, view);
		break;
	case 9:
		third = new loadOBJ("Resources/number_9.obj", shader1->ID);
		third->load(projection, view);
		break;
	default:
		third = new loadOBJ("Resources/number_0.obj", shader1->ID);
		third->load(projection, view);
		break;
	}


	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 scaling = glm::mat4(1.0f);

	translation = glm::translate(translation, glm::vec3(100.0f, y_pos, 100.0f));
	model = scaling * translation;
	third->setTransform(model);
	third->draw();
	delete third;

}
