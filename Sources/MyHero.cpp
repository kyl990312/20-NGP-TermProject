#include "MyHero.h"

void kyrHero::move() {
	// hero will move to its direction and jump
	// hero move to its direction
	if(!soul_moving)
		current_pos.z += 5;
	if (moving && !soul_moving) {
		on_the_log = false;
		log_speed = 0;
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
		// hero is jumping
		jumping_velocity -= 10;
		current_pos.y += jumping_velocity;
		//test
		if (current_pos.y <= 0.0f) {
			// hero fell to the floor
			// we have to init 'jumping values'
			moving = false;
			arrive_at_floor = true;
			jumping_velocity = 30.0f;
			current_pos.y = 0.0f;
		}
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
	// start checking
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
	obj.draw();
	soul_draw(projection,view,shader);

}

bool kyrHero::check_death(MyPos obs_pos,int obs_tag) {
	MyPos hero_view_pos = { current_pos.x * cos(glm::radians(10.0f)) - current_pos.z * sin(glm::radians(10.0f)),0.0f,current_pos.x*sin(glm::radians(10.0f)) + current_pos.z*cos(glm::radians(10.0f)) };
	if (hero_view_pos.z > 550 || hero_view_pos.x < -400 || hero_view_pos.x > 400) {
		soul_moving = true;
	}
	// case 1. collision with obstacles
	if (obs_tag == 1) {
		// obstacle is log
		if (check_collision(obs_pos,obs_tag)&& current_pos.y - obs_pos.y < 5) {
			// hero is on the log
			current_pos.y = obs_pos.y +size/2;
			// hero has to stop jumping
			arrive_at_floor = true;
			moving = false;
			on_the_log = true;
			fall_into_river = false;
			jumping_velocity = 30.0f;
			return false;
		}
		else {
			// hero falls into the river
			if (current_pos.y < obs_pos.y + size / 2) {
				fall_into_river = true;
				current_pos.y -= 5;
				moving = false;
				if (current_pos.y < -50) {
					soul_moving = true;
					current_pos.y += 5;
					return true;		
				}
			}
			else
				return false;
		}
	}
	else if (obs_tag == 2) {
		if (check_collision(obs_pos,obs_tag)) {
			// hero is on the common state
			// when collide with tree reverse the moving
			switch (int(direction_angle)) {
			case 0 :
				// when hero collide with tree change its state. and move it on that state
				cur_state_idx--;
			case 90:
				//move hero to rihgt
				current_pos.x -= 10;
				break;
			case -90:
				// move hero to left
				current_pos.x += 10;
				break;
			}
			return false;
		}		
	}
	else {
		if (check_collision(obs_pos,obs_tag)) {
			moving = false;
			soul_moving = true;
			return true;
		}
		else
			return false;
	}
}

void kyrHero::update(int tag,MyPos* obs_pos1, int obs_cnt1) {
	if (!soul_moving) {
		move();
		current_pos.x += log_speed;
		for (int i = 0; i < obs_cnt1; ++i) {
			if (check_death(obs_pos1[i], tag)) {

			}
		}
	}
	soul_move();
}

void kyrHero::soul_move() {
	if (soul_moving) {
		soul_pos.y += 5;
		soul_pos.x = 20*sin(glm::radians(soul_pos.y));
	}
}

void kyrHero::soul_draw(glm::mat4 projection, glm::mat4 view, Shader shader) {
	if (soul_moving){
		loadOBJ soul_obj("Resources/ghost.obj", shader.ID);
		soul_obj.load(projection, view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(soul_pos.x+current_pos.x, soul_pos.y+current_pos.y, current_pos.z));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

		soul_obj.setTransform(model);
		soul_obj.draw();
	}
}