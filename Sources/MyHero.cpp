#include "MyHero.h"

void kyrHero::Jump(int tag, MyPos* obs_pos, int obs_cnt1)
{
	std::cout << "JUMP" << std::endl;
	// Jump
	switch ((int)direction_angle) {
	case 0:
		// directon == front
		current_pos.z -= 10;
		break;
	case 90:
		// direction == right
		current_pos.x += 10;
		break;
	case -90:
		// direction == left
		current_pos.x -= 10;
		break;
	}
	// hero is jumping : frame : 5 , height : 30
	jump_DeltaX += 1.f;		// 0 ~ 5
	// 0 ~ 30  : 20, 30, 30, 20, 0
	current_pos.y = -5.f * jump_DeltaX * (jump_DeltaX - 5.f); 


	// Check Collsion
	switch (tag) {
	case MapState::River:
		for (int i = 0; i < obs_cnt1; i++) {
			// if True : Land on Log
			if (check_collision(obs_pos[i], tag)) {
				_state = HeroState::Float;
				current_pos.z = cur_mapState_posZ;
				current_pos.y = obs_pos->y + size / 2;
				jump_DeltaX = 0;
			}
		}
		break;
	case MapState::Common:
		for (int i = 0; i < obs_cnt1; i++) {
			if (check_collision(obs_pos[i], tag)) {
				switch ((int)direction_angle) {
				case 0:
					current_pos.x += 50;
					break;
				case -90:
					current_pos.x += 10;
					break;
				case 90:
					current_pos.x -= 10;
					break;
				}
			}
		}
		break;
	default:
		for (int i = 0; i < obs_cnt1; i++) {
			if (check_collision(obs_pos[i], tag)) {
				_state = HeroState::Die;
			}
		}
		break;
	}

	// Check where hero Land (except Landing at Log)
	if (current_pos.y <= 0) {
		if (tag == MapState::River) {
			current_pos.y -= 10;
			if (current_pos.y < -50)
				_state = HeroState::Die;
			return;
		}
		// set hero's positionZ at map's positionZ
		current_pos.z = cur_mapState_posZ;
		current_pos.y = 0.f;		
		_state = HeroState::Idle;
		jump_DeltaX = 0;
	}
}

void kyrHero::Float()
{
	std::cout << "Float" << std::endl;
	// move along the log
	current_pos.x += log_speed;

	// Check hero included in screen range
	MyPos hero_view_pos = { current_pos.x * cos(glm::radians(10.0f)) - current_pos.z * sin(glm::radians(10.0f)),0.0f,current_pos.x * sin(glm::radians(10.0f)) + current_pos.z * cos(glm::radians(10.0f)) };
	// screen out
	if (hero_view_pos.z > 550 || hero_view_pos.x < -400 || hero_view_pos.x > 400) {
		_state = HeroState::Die;
	}
}

bool kyrHero::check_collision(MyPos obs_pos, int obs_tag) {
	// make obs_bounding_box
	MyBoundingBox obs_bounding_box = {
		obs_pos.x + 20,20.0f,25.0f,
		obs_pos.x - 20,-20.0f,-25.0f
	};
	if (obs_tag == 3) {
		obs_bounding_box = {
		obs_pos.x + 400,25.0f,25.0f,
		obs_pos.x - 400,-25.0f,-25.0f
		};
	}
	// change my_bounding_box
	bounding_box = {
		current_pos.x + size / 2,current_pos.y + size / 2,current_pos.z + size / 2,
		current_pos.x - size / 2,current_pos.y - size / 2,current_pos.z - size / 2
	};

	// aabb - aabb collision checking
	if (bounding_box.right < obs_bounding_box.left)
		return false;

	if (bounding_box.left > obs_bounding_box.right)
		return false;

	if (bounding_box.top < obs_bounding_box.bottom)
		return false;
	if (bounding_box.bottom > obs_bounding_box.top)
		return false;
	return true;
}

void kyrHero::draw(glm::mat4 projection, glm::mat4 view, Shader shader) {
	loadOBJ obj("Resources/rabit.obj", shader.ID);
	shader.use();
	obj.load(projection, view);
	// init model_matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(current_pos.x, current_pos.y, current_pos.z));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-direction_angle), glm::vec3(0.0f, 1.0f, 0.0f));

	// lightning
	shader.setVec3("viewPos", glm::vec3(0.0f, 45.0f, 50));
	shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 0.9f));
	shader.setVec3("lightPos", glm::vec3(0, 800, 2000));

	// apply transform matix
	obj.setTransform(model);

	// draw obj
	if(_state == HeroState::Die)
		soul_draw(projection,view,shader);
	else
		obj.draw();

}

void kyrHero::update(int tag, MyPos* obs_pos1, int obs_cnt1) {
		
	if (_state != HeroState::Die)
		// move backward following map
		current_pos.z += 5;
	MyPos hero_view_pos = { current_pos.x * cos(glm::radians(10.0f)) - current_pos.z * sin(glm::radians(10.0f)),0.0f,current_pos.x * sin(glm::radians(10.0f)) + current_pos.z * cos(glm::radians(10.0f)) };

	switch (_state)
	{
	case HeroState::Idle:
		std::cout << "Idle" << std::endl;
		// Check hero included in screen range			
		// screen out
		if (hero_view_pos.z > 550 || hero_view_pos.x < -400 || hero_view_pos.x > 400) {
			_state = HeroState::Die;
		}

		// check collision
		if (tag == MapState::Road || tag == MapState::Trail) {
			for (int i = 0; i < obs_cnt1; i++) {
				if (check_collision(obs_pos1[i], tag)) {
					_state = HeroState::Die;
				}
			}
		}
		break;
	case HeroState::Jump:
		Jump(tag, obs_pos1, obs_cnt1);
		break;
	case HeroState::Float:
		Float();
		break;
	case HeroState::Die:
		std::cout << "Die" << std::endl;
		Die();
		break;
	}
	
}

void kyrHero::Die() {
	soul_pos.y += 5;
	soul_pos.x = 20*sin(glm::radians(soul_pos.y));
}

void kyrHero::soul_draw(glm::mat4 projection, glm::mat4 view, Shader shader){

	loadOBJ soul_obj("Resources/ghost.obj", shader.ID);
	soul_obj.load(projection, view);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(soul_pos.x+current_pos.x, soul_pos.y+current_pos.y, current_pos.z));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

	soul_obj.setTransform(model);
	soul_obj.draw();

}