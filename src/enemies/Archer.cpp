#include "Utils.h"
#include "Game.h"
#include "Player.h"
#include "Arrow.h"

#include "Archer.h"

BITMAP *Archer::_sprite = 0;

void Archer::Update()
{
	if(!shooting)
	{
		walkCounter--;
		if(walkCounter <= 0)
		{
			orientation = rand() % 4;
			counter = 0;
			walkCounter = walkTime;
		}
		if(x <= 0) orientation = 3;
		if(x >= 630) orientation = 2;
		if(y <= 0) orientation = 1;
		if(y >= 420) orientation = 0;
		frameStart = 0;
		frameEnd = 3;
		switch(orientation)
		{
			case 0:
				MoveSolid(0, -walkSpeed);
				if(GetMinDy() == 0) walkCounter = 0;
				break;
			case 1:
				MoveSolid(0, walkSpeed);
				if(GetMaxDy() == 0) walkCounter = 0;
				break;
			case 2:
				MoveSolid(-walkSpeed, 0);
				if(GetMinDx() == 0) walkCounter = 0;
				break;
			case 3:
				MoveSolid(walkSpeed, 0);
				if(GetMaxDx() == 0) walkCounter = 0;
				break;
		}
		pathIntegral += walkSpeed;
		if(pathIntegral > arrowDistance)
		{
			backupOrientation = orientation;
			Orientate(game.player->x - x, game.player->y - y);
			shooting = true;
			pathIntegral -= arrowDistance;
			frameStart = 4;
			frameEnd = 6;
			counter = 0;
			inverseSpeed = shootAnimSpeed;
			hasShot = false;
		}
	}
	SpriteEntity::Update();
	if(frame == 5)
	{
		if(!hasShot)
		{
			hasShot = true;
			Entity *arrow = new Arrow(x + width / 2, y + height / 2, LineAngle(x + width / 2, y + height / 2, game.player->x + game.player->width / 2, game.player->y + game.player->height / 2));
			game.entitiesManager.Add(arrow);
			arrow = new Arrow(x + width / 2, y + height / 2, LineAngle(x + width / 2, y + height / 2, game.player->x + game.player->width / 2, game.player->y + game.player->height / 2) - M_PI * 0.125);
			game.entitiesManager.Add(arrow);
			arrow = new Arrow(x + width / 2, y + height / 2, LineAngle(x + width / 2, y + height / 2, game.player->x + game.player->width / 2, game.player->y + game.player->height / 2) + M_PI * 0.125);
			game.entitiesManager.Add(arrow);
			PlaySample(arrowSounds[rand() % 3]);
		}
	}
	if(frame == 6)
	{
		frameStart = 0;
		frameEnd = 3;
		inverseSpeed = walkAnimSpeed;
		counter = 0;
		shooting = false;
		orientation = backupOrientation;
	}
}

Archer::Archer()
{
	arrowSounds[0] = (SAMPLE *) game.GetData("snd_arrow1");
	arrowSounds[1] = (SAMPLE *) game.GetData("snd_arrow2");
	arrowSounds[2] = (SAMPLE *) game.GetData("snd_arrow3");
	if(_sprite == 0) _sprite = (BITMAP *) game.GetData("spr_archer"); // load_bitmap("archer.bmp", 0);
	sprite = _sprite;
	width = 20;
	height = 20;
	offsetX = 10;
	offsetY = 15;
	spriteWidth = 40;
	spriteHeight = 40;
	health = 2;
	inverseSpeed = 6;
	frameStart = 0;
	frameEnd = 3;
	walkTime = 25 + std::rand() % 10;
	walkSpeed = 1.75 + (0.075 * float(std::rand() % 11));
	walkCounter = 0;
	orientation = 0;
	pathIntegral = 0;
	MoveToFreeSpot(60, 60, 570, 360);
	shooting = false;
	arrowDistance = 100 + std::rand() % 150;
	walkAnimSpeed = 6;
	shootAnimSpeed = 15;
	hasShot = false;
}