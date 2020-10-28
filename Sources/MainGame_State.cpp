#include "MainGame_State.h"
// this is main game state

MainGame_State::MainGame_State() {
	//test
	PlaySound(TEXT("Resources/Spongebob.wav"), NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP);
	init_map();
}

MainGame_State::~MainGame_State() {
	std::ofstream out("Resources/rank.txt", std::ios::app);
	out << pass_state_cnt << '\n';
	out.close();
	for (int i = 0; i < map_count;++i) {
		delete states[i];
	}
	delete states;
}

void MainGame_State::Display() {
	for (int i = 0; i < map_count; i++) {
		states[i]->draw(projection, view, *shader);
		if (states[i]->check_removing()) {
			delete states[i];
			int create_state_random = rand() % 5;
			switch (create_state_random)
			{
			case 0:
				states[i] = new MyRoad;
				break;
			case 1:
				states[i] = new MyRiver;
				break;
			case 2:
				states[i] = new MyTrail;
				break;
			default:
				states[i] = new MyCommon;
				break;
			}
			states[i]->pos.z = -545;
		}
	}

	// hero draw
	hero.draw(projection, view, *hero_shader);
}

void MainGame_State::update() {
	if (start) {
		// change this code into using 'for'
		if (!hero.soul_moving) {
			for (int i = 0; i < map_count; i++) {
				states[i]->move();
				states[i]->pos.z += 5;
			}
		}
		//hero
		hero_update();
	}
	if (hero.soul_moving) {
		if (back_music) {
			PlaySound(TEXT("Resources/fail2.wav"), NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC);
			back_music = false;
		}
		change_timer -= 1;
		if (change_timer < 0) {
			next_state = 2;
		}
	}
}

void MainGame_State::keyboard(unsigned char key, int x, int y) {
	if (!hero.soul_moving && !hero.moving && !hero.fall_into_river) {
		//PlaySound(TEXT("./jump2.wav"), NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC);
		switch (key) {
		case 'w':
		case 'W':
			// move hero to front
			hero.direction_angle = 0.0f;
			// this is needed to move hero to side when collide with tree
			cur_state_idx = (cur_state_idx + 1) % map_count;
			pass_state_cnt += 1;
			break;
		case 'd':
		case 'D':
			//move hero to rihgt
			hero.direction_angle = 90.0f;
			break;
		case 'a':
		case 'A':
			// move hero to left
			hero.direction_angle = -90.0f;
			break;
		default:
			return;
		}
		hero.moving = true;
		start = true;
	}
}

void MainGame_State::init_map() {
	states[0] = new MyCommon;
	if (fabs(states[0]->collision_pos[0].x - hero.current_pos.x) < 50) {
		hero.current_pos.x += 50;
	}
	if (fabs(states[0]->collision_pos[1].x - hero.current_pos.x) < 50) {
		hero.current_pos.x += 50;
	}
	if (fabs(states[0]->collision_pos[2].x - hero.current_pos.x) < 50) {
		hero.current_pos.x += 50;
	}
	//create states
	for (int i = 1; i < map_count; i++) {
		int create_state_random = rand() % 7;
		switch (create_state_random)
		{
		case 0:
		case 1:
			states[i] = new MyRoad;
			break;
		case 2:
		case 3:
			states[i] = new MyRiver;
			break;
		case 4:
			states[i] = new MyTrail;
			break;
		default:
			states[i] = new MyCommon;
			break;
		}
		states[i]->pos.z = i * -50;
	}
}

void MainGame_State::hero_update() {
	// get current state's obstacles pos
	cur_state_obs_pos[0] = states[cur_state_idx]->collision_pos[0];
	cur_state_obs_pos[1] = states[cur_state_idx]->collision_pos[1];
	cur_state_obs_pos[2] = states[cur_state_idx]->collision_pos[2];
	// get current state's obstacles count
	cur_state_obs_cnt = states[cur_state_idx]->obs_cnt;
	// get current state's tag
	cur_state_tag = states[cur_state_idx]->tag;
	if (hero.on_the_log) {
		// when hero is on the log run this code
		hero.log_speed = states[cur_state_idx]->get_obs_speed(0);
	}
	hero.update(cur_state_tag, cur_state_obs_pos, cur_state_obs_cnt);
	// hero arrived at floor. hero was jumping before
	if (hero.arrive_at_floor && hero.direction_angle == 0.0f) {
		hero.arrive_at_floor = false;
		hero.current_pos.z = states[cur_state_idx]->pos.z;
	}
}