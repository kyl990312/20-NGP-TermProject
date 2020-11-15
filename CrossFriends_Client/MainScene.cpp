#include "MainScene.h"

MainScene::MainScene()
{
	Init();
}

MainScene::~MainScene()
{
	DeleteMap();
}

void MainScene::Update(float elapsedTime)
{
	if (start) {
		// map moving
		if (hero.m_state != HeroState::Die) {
			for (int i = 0; i < map_count; i++) {
				states[i]->Update(elapsedTime);
			}
		}
		//hero
		// get current state's obstacles pos
		cur_state_obs_pos[0] = states[cur_state_idx]->collisionPosition[0];
		cur_state_obs_pos[1] = states[cur_state_idx]->collisionPosition[1];
		cur_state_obs_pos[2] = states[cur_state_idx]->collisionPosition[2];
		// get current state's obstacles count
		cur_state_obs_cnt = states[cur_state_idx]->m_obsCnt;
		// get current state's tag
		cur_state_tag = states[cur_state_idx]->m_tag;
		if (hero.m_state == HeroState::Float) {
			// when hero is on the log run this code
			hero.logVelocityX = states[cur_state_idx]->Get(0);
		}
		hero.update(cur_state_tag, cur_state_obs_pos, cur_state_obs_cnt);
		hero.cur_mapState_posZ = states[cur_state_idx]->pos.z;
	}
	if (hero.m_state == HeroState::Die) {
		if (back_music) {
			PlaySound(TEXT("Resources/fail2.wav"), NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC);
			back_music = false;
		}
	}
}

void MainScene::Render()
{

}

void MainScene::Init()
{
	PlaySound(TEXT("Resources/Spongebob.wav"), NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP);
	InitMap();
	hero.Init();
}

void MainScene::Keyboard(unsigned char key)
{
}

void MainScene::InitMap()
{
	states[0] = new Common;
	if (fabs(states[0]->collisionPosition[0].x - hero.GetPosition().x) < 50) {
		glm::vec3 position = hero.GetPosition();
		position.x += 50;
		hero.SetPosition(position);
	}
	if (fabs(states[0]->collisionPosition[1].x - hero.GetPosition().x) < 50) {
		glm::vec3 position = hero.GetPosition();
		position.x += 50;
		hero.SetPosition(position);
	}
	if (fabs(states[0]->collisionPosition[2].x - hero.GetPosition().x) < 50) {
		glm::vec3 position = hero.GetPosition();
		position.x += 50;
		hero.SetPosition(position);
	}
	//create states
	for (int i = 1; i < map_count; i++) {
		int create_state_random = rand() % 7;
		switch (create_state_random)
		{
		case 0:
		case 1:
			states[i] = new Road;
			break;
		case 2:
		case 3:
			states[i] = new River;
			break;
		case 4:
			states[i] = new Trail;
			break;
		default:
			states[i] = new Common;
			break;
		}
		glm::vec3 position = states[i]->GetPosition();			
		position.z = i * -50;
		states[i]->SetPosition(position);
	}
}

void MainScene::DeleteMap()
{
	for(int i = 0 ; i <map_count;i++){
		if (states[i] != NULL)
			delete states[i];
	}
	if (states != NULL)
		delete states;
}
