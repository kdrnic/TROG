#include "Utils.h"
#include "Game.h"
#include "DevilProjectile.h"

#include "Devil.h"

#include <cmath>

#define ENDFRAME 0
#define ANIMSPEED 6
#define SPEED 3
#define PROJCOUNTERMIN 55
#define PROJCOUNTERMAX 80
#define LEADPROB 33
#define PROJSPEED 5
#define PROJDMG 3

#define ANGMIN 120
#define ANGMAX 240

#define ANGSPEED 0.05

#define DHEALTH 9

#define TALKMAX 60

#define MAXDEVILS 2

bool ShallTalk()
{
	static int counter = -1;
	counter++;
	return (!counter);
}

bool Devil::Is(std::string what)
{
	if(what == "DEVIL") return true;
	if(what == "SOLID") return false;
	return Enemy::Is(what);
}

void Devil::Update()
{
	if(!hasTalked)
	{
		talkCounter++;
		if(talkCounter > TALKMAX)
		{
			hasTalked = true;
			if(ShallTalk())
			{
				game.PushDialogLine("Hello!");
				game.PushDialogLine("I am a \"tampered savegame file\" devil!");
			}
		}
	}
	
	x += SPEED * std::cos(angle);
	y += SPEED * std::sin(angle);
	angle += dAngle * ANGSPEED;
	
	angCounter--;
	if(angCounter <= 0)
	{
		angCounter = ANGMIN + (std::rand() % (ANGMAX - ANGMIN));
		dAngle *= -1;
	}
	
	projCounter--;
	if(projCounter <= 0)
	{
		float selfX, selfY, targX, targY;
		GetCenter(selfX, selfY);
		game.player->GetCenter(targX, targY);
		if(std::rand() % 100 <= LEADPROB)
		{
			float distance = (selfX - targX);
			distance = distance * distance;
			distance += (selfY - targY) * (selfY - targY);
			distance = std::sqrt(distance);
			
			targX += game.player->speedX * (distance / PROJSPEED);
			targY += game.player->speedY * (distance / PROJSPEED);
		}
		
		float pAngle = LineAngle(selfX, selfY, targX, targY);
		
		DevilProjectile *proj = new DevilProjectile(x + width / 2, y + height / 2, std::cos(pAngle) * PROJSPEED, std::sin(pAngle) * PROJSPEED);
		proj->hitDamage = PROJDMG;
		game.entitiesManager.Add((Entity *) proj);
		
		PlaySample((SAMPLE *) game.GetData("snd_devilproj"));
		
		projCounter = PROJCOUNTERMIN + (std::rand() % (PROJCOUNTERMAX - PROJCOUNTERMIN));
	}
	
	if(x < 0 - spriteWidth) x = 630 + spriteWidth;
	if(x > 630 + spriteWidth) x = 0 - spriteWidth;
	if(y < 0 - spriteHeight) y = 420 + spriteHeight;
	if(y > 420 + spriteHeight) y = 0 - spriteHeight;
}

Devil::Devil()
{
	sprite = (BITMAP *) game.GetData("spr_devil");
	width = 25;
	height = 25;
	offsetX = (sprite->w - width) / 2;
	offsetY = (sprite->w - height) / 2;
	spriteWidth = sprite->w;
	spriteHeight = sprite->w;
	health = DHEALTH;
	inverseSpeed = ANIMSPEED;
	frameStart = 0;
	frameEnd = ENDFRAME;
	orientation = 0;
	projCounter = 0;
	angle = double(std::rand() % 1000) * M_PI * 1.0 / 500.0;
	angCounter = 0;
	if(std::rand() % 100 < 50) dAngle = 1;
	else dAngle = -1;
	
	layer = 1;
	
	persistent = true;
	
	talkCounter = 0;	
	hasTalked = false;
	
	if(game.entitiesManager.Count("DEVIL") >= MAXDEVILS) alive = false;
}