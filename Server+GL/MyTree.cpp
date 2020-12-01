#include "MyTree.h"

extern loadOBJ models[26];

MyTree::MyTree(MyPos road_pos) {
	// pos init
	pos = { (float)((rand() % 24 - 12) * 50),road_pos.y,road_pos.z };
	size = (float)(rand() % 2 + 1);
}

void MyTree::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, Shader shader) {
	//loadOBJ obj(obj_path, shader.ID);
	//shader.use();
	models[19].load(projection, view);

	// change road's positoin 
	model = glm::translate(model, glm::vec3(pos.x, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, size, 1.0f));
	models[19].setTransform(model);

	models[19].draw();
}

void MyTree::move(MyPos road_pos) {
}

bool MyTree::check_removing() {
	return false;
}

MyTree::~MyTree() {

};