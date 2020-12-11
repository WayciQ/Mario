#include  "PlayerWorlMapState.h"
#include "PlayScene.h"
PlayerWorlMapState::PlayerWorlMapState(int move)
{
	player->gravity = 0;
	player->vx = 0;
	player->vy = 0;
	this->move = move;
	int a = camera->maxLeftCam;
	int b = camera->maxTopCam;
	int cellx = int(player->x) - a;
	int celly = int(player->y) - b;
	stateName = IDLE_WORLD_MAP;
	
	switch (move)
	{
	case 0:
		posX = int(cellx / 16) * 16;
		posY = int(celly / 16) * 16;
		break;
	case 1:
		player->vx = +0.1f;
		posY = int(player->y);
		posX = int(player->x) + 32;
		break;
	case -1:
		player->vx = -0.1f;
		posY = int(player->y);
		posX = int(player->x) - 32;
		break;
	case 2:
		player->vy = +0.1f;
		posX = int(player->x);
		posY = int(player->y) + 32;
		break;
	case -2:
		player->vy = -0.1f;
		posX = int(player->x);
		posY = int(player->y) - 32;
		break;
	default:
		break;
	}
	
}
void PlayerWorlMapState::HandleKeyBoard()
{
	
}
void PlayerWorlMapState::Update(DWORD dt)
{

	switch (move)
	{
	case 0:
		player->vy = 0;
		player->vx = 0;
		break;
	case 1:
		
		if (player->x >= posX)
		{
			player->x = posX; 
			player->vx = 0;
		}
		break;
	case -1:
		if (player->x <= posX)
		{
			player->x = posX; 
			player->vx = 0;
		}
		break;
	case 2:
		if (player->y >= posY)
		{
			player->y = posY; 
			player->vy = 0;
		}
		break;
	case -2:
		if (player->y <= posY)
		{
			player->y = posY;
			player->vy = 0;
		}
		break;
	}
	
}
PlayerWorlMapState::~PlayerWorlMapState(){}
