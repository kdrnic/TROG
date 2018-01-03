#include "Game.h"

#include <allegro.h>

#include "SpriteEntity.h"

void SpriteEntity::Draw(BITMAP *doubleBuffer)
{
	frame = frameStart + ((counter / inverseSpeed) % (frameEnd - frameStart + 1));
	if(sprite != 0) masked_blit(sprite, doubleBuffer, orientation * spriteWidth, frame * spriteHeight, x - offsetX, y - offsetY, spriteWidth, spriteHeight);
}

void SpriteEntity::Update()
{
	counter++;
	frame = frameStart + ((counter / inverseSpeed) % (frameEnd - frameStart + 1));
	nextFrame = frameStart + (((counter + 1) / inverseSpeed) % (frameEnd - frameStart + 1));
}

 void SpriteEntity::SetParameter(std::string p, std::string v)
 {
	 if(p == "sprite")
	 {
		 sprite = (BITMAP *) game.GetData(v.c_str());
		 return;
	 }
	 if(p == "orientation")
	 {
		 orientation = std::atoi(v.c_str());
		 return;
	 }
	 Entity::SetParameter(p, v);
 }

void SpriteEntity::Orientate(float dx, float dy)
{
	if(dx == dy) return;
	if(dx == 0)
	{
		if(dy < 0) orientation = 0;
		if(dy > 0) orientation = 1;
	}
	else
	{
		float ratio;
		if(dx < 0) ratio = dy / (0 - dx);
		else ratio = dy / dx;
		if(ratio <= -0.5) orientation = 0;
		else if(ratio >= 0.5) orientation = 1;		
		else if(dx > 0) orientation = 3;
		else orientation = 2;
	}
}

int SpriteEntity::RandomOrientation(int o)
{
	return orientation = rand() % 4;
}

SpriteEntity::SpriteEntity()
{
	counter = frame = orientation = frameStart = frameEnd = offsetX = offsetY = 0;
	inverseSpeed = 1;
	sprite = 0;
}