#include "MainGame_State.h"
#include"FirstState.h"
// this is main game state
extern float elapsedTimeSec;

MainGame_State::MainGame_State() {
	//test
	//PlaySound(TEXT("Resources/Spongebob.wav"), NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP);
	init_map();
}

MainGame_State::~MainGame_State() {
	std::ofstream out("rank.txt", std::ios::app);
	out << pass_state_cnt << '\n';
	out.close();
	for (int i = 0; i < map_count;++i) {
		if(states[i] != NULL)
			delete states[i];
	}
	if(states != NULL)
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
	for(int i = 0 ; i<1;++i)
		hero[i].draw(projection, view, *hero_shader);
}

void MainGame_State::update() {
	if (start) {
		// map moving
		if (hero[0]._state != HeroState::Die || hero[1]._state != HeroState::Die || hero[2]._state != HeroState::Die) {
			for (int i = 0; i < map_count; i++) {
				states[i]->move();
				states[i]->pos.z += 5 * elapsedTimeSec * SPEED;
			}
		}
		
		//hero
		for(int i = 0 ; i <3; ++i)
			hero_update(i);
		for (int i = 0; i < 3; ++i) {
			hero[i].otherHero[0]=hero[(i+1)%3].current_pos;
			hero[i].otherHero[1]=hero[(i+2)%3].current_pos;
		}
	}
	if (hero[0]._state == HeroState::Die && hero[1]._state == HeroState::Die && hero[2]._state == HeroState::Die) {
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
	if (hero[x]._state == HeroState::Idle || hero[x]._state == HeroState::Float) {
		hero[x].prevPosition = hero[x].current_pos;
		switch (key) {
		case 'w':
		case 'W':
			// move hero to front
			hero[x].direction_angle = 0.0f;
			// this is needed to move hero to side when collide with tree
			cur_state_idx[x] = (cur_state_idx[x] + 1) % map_count;
			pass_state_cnt += 1;
			break;
		case 'd':
		case 'D':
			//move hero to rihgt
			hero[x].direction_angle = 90.0f;
			break;
		case 'a':
		case 'A':
			// move hero to left
			hero[x].direction_angle = -90.0f;
			break;
		default:
			return;
		}
		hero[x]._state = HeroState::Jump;
		start = true;
	}
}

void MainGame_State::init_map() {
	for (int i = 0; i < 3; ++i) {
		hero[i].current_pos.x = (i - 1) * 50.0f;
	}
	states[0] = new MyCommon;
	states[0]->obs_cnt = 0;
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

void MainGame_State::hero_update(int idx) {
	// get current state's obstacles pos
	cur_state_obs_pos[idx][0] = states[cur_state_idx[idx]]->collision_pos[0];
	cur_state_obs_pos[idx][1] = states[cur_state_idx[idx]]->collision_pos[1];
	cur_state_obs_pos[idx][2] = states[cur_state_idx[idx]]->collision_pos[2];
	// get current state's obstacles count
	cur_state_obs_cnt[idx] = states[cur_state_idx[idx]]->obs_cnt;
	// get current state's tag
	cur_state_tag[idx] = states[cur_state_idx[idx]]->tag;
	if (hero[idx]._state == HeroState::Float) {
		// when hero is on the log run this code
		hero[idx].log_speed = states[cur_state_idx[idx]]->get_obs_speed(0);
	}
	hero[idx].cur_mapState_posZ = states[cur_state_idx[idx]]->pos.z;
	hero[idx].update(cur_state_tag[idx], cur_state_obs_pos[idx], cur_state_obs_cnt[idx]);
}

void MainGame_State::GetMapDatas(ObjectData* mapDatas)
{
	// set MapDatas
	for (int i = 0; i < map_count; ++i) {
		mapDatas[i].positionX = states[i]->pos.x;
		mapDatas[i].positionY = states[i]->pos.y;
		mapDatas[i].positionZ = states[i]->pos.z;
		mapDatas[i].rotationX = 0.0f;
		mapDatas[i].rotationY = 0.0f;
		mapDatas[i].rotationZ = 0.0f;
		mapDatas[i].sizeX = 1.f;
		mapDatas[i].sizeY = 1.f;
		mapDatas[i].sizeZ = 1.f;
		switch (states[i]->tag) {
		case MapState::Common:
			mapDatas[i].tag = ModelIdx::COMMON;
			break;
		case MapState::River:
			mapDatas[i].tag = ModelIdx::RIVER;
			break;
		case MapState::Road:
			mapDatas[i].tag = ModelIdx::ROAD;
			break;
		case MapState::Trail:
			mapDatas[i].tag = ModelIdx::TAIL;
			break;
		}
	}

	// set ObstacleDatas
	int idx = 23;
	for (int i = 0; i < map_count; ++i) {
		for (int j = 0; j < states[i]->obs_cnt; ++j) {
			mapDatas[idx].positionX = states[i]->collision_pos[j].x;
			mapDatas[idx].positionY = states[i]->collision_pos[j].y;
			mapDatas[idx].positionZ = states[i]->pos.z;
			mapDatas[idx].rotationX = states[i]->obsRotation[0].x;
			mapDatas[idx].rotationY = states[i]->obsRotation[0].y;
			mapDatas[idx].rotationZ = states[i]->obsRotation[0].z;
			mapDatas[idx].sizeX = states[i]->obsSize[j].x;
			mapDatas[idx].sizeY = states[i]->obsSize[j].y;
			mapDatas[idx].sizeZ = states[i]->obsSize[j].z;
			mapDatas[idx].tag = states[i]->obsTags[j];
			idx++;
		}
	}

	for (; idx < 100; ++idx) {
		mapDatas[idx].tag = -1;
		mapDatas[idx].positionX = 0.0f;
		mapDatas[idx].positionY = 0.0f;
		mapDatas[idx].positionZ = 0.0f;
		mapDatas[idx].rotationX = 0.0f;
		mapDatas[idx].rotationY = 0.0f;
		mapDatas[idx].rotationZ = 0.0f;
		mapDatas[idx].sizeX = 0.0f;
		mapDatas[idx].sizeY = 0.0f;
		mapDatas[idx].sizeZ = 0.0f;
	}
}

void MainGame_State::GetHeroDatas(HeroData* herodatas)
{
	for (int i = 0; i < 3; ++i) {
		if (hero[i]._state == HeroState::Die) {
			herodatas[i].x = hero[i].current_pos.x + hero[i].soul_pos.x;
			herodatas[i].y = hero[i].current_pos.y + hero[i].soul_pos.y;
			herodatas[i].z = hero[i].current_pos.z;

			herodatas[i].rotaionAngle = 0.f;
		}
		else {
			herodatas[i].x = hero[i].current_pos.x;
			herodatas[i].y = hero[i].current_pos.y;
			herodatas[i].z = hero[i].current_pos.z;

			herodatas[i].rotaionAngle = 180 - hero[i].direction_angle;

		}
		bool alive;
		if (hero[i]._state != HeroState::Die)
			alive = true;
		else
			alive = false;
		herodatas[i].alive = alive;
	}
}

void MainGame_State::Init()
{
	//test
	//PlaySound(TEXT("Resources/Spongebob.wav"), NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP);
	init_map();
}

void MainGame_State::DeleteAll()
{
	for (int i = 0; i < map_count; i++) {
		if (states[i] != NULL)
			delete states[i];
	}

	if (states != NULL)
		delete states;
}

