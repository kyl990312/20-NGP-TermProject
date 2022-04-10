#include "MyHero.h"

extern float elapsedTimeSec;

void kyrHero::Jump(int tag, glm::vec3* obs_pos, int obs_cnt1)
{

	// Jump
	switch ((int)direction_angle) {
	case 0:
		// directon == front
		current_pos.z -= 10 * SPEED * elapsedTimeSec;
		break;
	case 90:
		// direction == right
		current_pos.x += 10 * SPEED * elapsedTimeSec;
		break;
	case -90:
		// direction == left
		current_pos.x -= 10 * SPEED * elapsedTimeSec;
		break;
	}
	// hero is jumping : frame : 5 , height : 30
	jump_DeltaX += 1.f * elapsedTimeSec* SPEED;		// 0 ~ 5
	// 0 ~ 30  : 20, 30, 30, 20, 0
	current_pos.y = -5.f * jump_DeltaX * (jump_DeltaX - 5.f) + addedY; 

	// Check Collsion
	for (int i = 0; i < 2; ++i) {
		if (CheckCollistionWithHero(otherHero[i],40)) {
			if (direction_angle == 0) {
				current_pos.x += 50.f;
			}
			else {
				current_pos = prevPosition;
			}
		}
	}

	switch (tag) {
	case MapState::River:
		if (jump_DeltaX > 5) {
			for (int i = 0; i < obs_cnt1; i++) {
				// if True : Land on Log
				if (check_collision(obs_pos[i], tag)) {
					_state = HeroState::Float;
					current_pos.z = cur_mapState_posZ;
					current_pos.y = obs_pos->y + size / 2;
					jump_DeltaX = 0;
					addedY = current_pos.y + 5;
				}
			}
		}
		break;
	case MapState::Common:
		for (int i = 0; i < obs_cnt1; i++) {
			if (check_collision(obs_pos[i], tag)) {
				if (direction_angle == 0) {
					current_pos.x += 50.f;
				}
				else {
					current_pos = prevPosition;
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
			current_pos.y -= 10 * elapsedTimeSec;
			if (current_pos.y < -50)
				_state = HeroState::Die;
			return;
		}
		// set hero's positionZ at map's positionZ
		current_pos.z = cur_mapState_posZ;
		current_pos.y = 0.f;		
		addedY = 0.f;
		_state = HeroState::Idle;
		jump_DeltaX = 0;
	}
}

void kyrHero::Float()
{

	// move along the log
	current_pos.x += log_speed * elapsedTimeSec * SPEED;

	// Check hero included in screen range
	glm::vec3 hero_view_pos = { current_pos.x * cos(glm::radians(10.0f)) - current_pos.z * sin(glm::radians(10.0f)),0.0f,current_pos.x * sin(glm::radians(10.0f)) + current_pos.z * cos(glm::radians(10.0f)) };
	// screen out
	if (hero_view_pos.z > 550 || hero_view_pos.x < -400 || hero_view_pos.x > 400) {
		_state = HeroState::Die;
	}
}

bool kyrHero::check_collision(glm::vec3 obs_pos, int obs_tag) {
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


void kyrHero::update(int tag, glm::vec3* obs_pos1, int obs_cnt1) {
		
	// move backward following map
	current_pos.z += 5 * elapsedTimeSec * SPEED;
	glm::vec3 hero_view_pos = { current_pos.x * cos(glm::radians(10.0f)) - current_pos.z * sin(glm::radians(10.0f)),0.0f,current_pos.x * sin(glm::radians(10.0f)) + current_pos.z * cos(glm::radians(10.0f)) };

	switch (_state)
	{
	case HeroState::Idle:

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

		Die();
		break;
	}	
}

void kyrHero::Die() {
	soul_pos.y += 5 * elapsedTimeSec * SPEED;
	soul_pos.x = 20*sin(glm::radians(soul_pos.y));
	soul_pos.z -= 5 * elapsedTimeSec * SPEED;
}



bool kyrHero::CheckCollistionWithHero(glm::vec3 position, float size)
{
	float aMinX, aMinY, aMinZ, aMaxX, aMaxY, aMaxZ;
	float bMinX, bMinY, bMinZ, bMaxX, bMaxY, bMaxZ;

	aMinX = current_pos.x - size / 2;
	aMinY = current_pos.y - size / 2;
	aMinZ = current_pos.z - size / 2;
	aMaxX = current_pos.x + size / 2;
	aMaxY = current_pos.y + size / 2;
	aMaxZ = current_pos.z + size / 2;

	bMinX = position.x - size / 2;
	bMinY = position.y - size / 2;
	bMinZ = position.z - size / 2;
	bMaxX = position.x + size / 2;
	bMaxY = position.y + size / 2;
	bMaxZ = position.z + size / 2;

	if (aMinX > bMaxX)
		return false;
	if (aMaxX < bMinX)
		return false;

	if (aMinY > bMaxY)
		return false;
	if (aMaxY < bMinY)
		return false;

	if (aMinZ > bMaxZ)
		return false;
	if (aMaxZ < bMinZ)
		return false;

	return true;
}

