#include <cstdlib>
#include <iostream>
#include <cmath>
#include <allegro.h>

#include "Game.h"
#include "Entity.h"

const float blockWidth = 15.0f;
const float blockHeight = 15.0f;

bool Entity::Is(std::string what)
{
	return false;
}

void Entity::Draw(BITMAP *bmp)
{
}

void Entity::Update()
{
}

void Entity::OnCollision(Entity *e)
{
}

void Entity::SetParameter(std::string p, std::string v)
{
	if(p == "x" && !ignorePos) x = std::atoi(v.c_str());
	if(p == "y" && !ignorePos) y = std::atoi(v.c_str());
	if(p == "randomize_pos")
	{
		ignorePos = true;
		MoveToFreeSpot();
	}
}

bool Entity::Collision(Entity *e)
{
	if(e->x + e->width - 1< x) return false;
	if(e->x > x + width - 1) return false;
	if(e->y + e->height - 1 < y) return false;
	if(e->y > y + height - 1) return false;
	return true;
}

bool Entity::Collision(int _x, int _y, int _w, int _h)
{
	if(_x + _w - 1< x) return false;
	if(_x > x + width - 1) return false;
	if(_y + _h - 1 < y) return false;
	if(_y > y + height - 1) return false;
	return true;
}

void Entity::GetCenter(float &_x, float &_y)
{
	_x = x + width * 0.5;
	_y = y + height * 0.5;
}

void Entity::GetCenter(int &_x, int &_y)
{
	_x = x + width * 0.5;
	_y = y + height * 0.5;
}

Entity::Entity()
{
	ignorePos = false;
	alive = true;
	persistent = false;
	layer = 0;
}

bool Entity::IsEntitySolid(Entity *e)
{
	return e->Is("SOLID");
}

bool Entity::IsBlockSolid(int b)
{
	return (b & 1);
}

bool Entity::MapCollision()
{
	for(int bx = std::floor(x / blockWidth); (bx * blockWidth) <= std::floor(x + width - 1); bx++)
	{
		for(int by = std::floor(y / blockHeight); (by * blockHeight) <= std::floor(y + height - 1); by++)
		{
			if(by < 0) continue;
			if(IsBlockSolid(game.mapManager.BlockTypeAt(bx, by))) return true;
			if(by == 27) break;
		}
		if(bx == 41) break;
	}
	return false;
}

void Entity::MoveToFreeSpot(int minX, int minY, int maxX, int maxY)
{
	bool collided = true;
	while(collided)
	{
		x = (rand() % 42) * blockWidth;
		y = (rand() % 28) * blockHeight;
		collided = MapCollision();
		Entity *entities[999];
		int n = game.entitiesManager.SearchArea(x, y, width, height, entities, 999);
		for(int i = 0; i < n; i++)
		{
			if(entities[i] == this) continue;
			if(IsEntitySolid(entities[i])) collided = true;
		}
		if(x < minX) collided = true;
		if(y < minY) collided = true;
		if(x + width > maxX) collided = true;
		if(y + height > maxY) collided = true;
	}
}

float Entity::GetMaxDx()
{
	int iXPlusW = int(std::ceil(x + width));
	int iY = int(std::ceil(y));
	int iYPlusH = int(std::ceil(y + height)) - 1;
	float maxDxB = 999;
	for(int bx = iXPlusW / blockWidth; bx < 42; bx++)
	{
		for(int by = iY / blockHeight; by <= iYPlusH / blockHeight; by++)
		{
			if(IsBlockSolid(game.mapManager.BlockTypeAt(bx, by)))
			{
				maxDxB = float(bx * blockWidth) - width - x;
			}
			if(maxDxB != 999) break;
		}
		if(maxDxB != 999) break;
	}
	float maxDxE = 999;
	Entity *entities[20];
	int n = game.entitiesManager.SearchArea(x + width, y, 999, height, entities, 20);
	for(int i = 0; i < n; i++)
	{
		if(entities[i] == this) continue;
		if(!IsEntitySolid(entities[i])) continue;
		if(entities[i]->x - x - width < maxDxE) maxDxE = entities[i]->x - x - width;
	}
	if(maxDxB < maxDxE) return maxDxB;
	else return maxDxE;
}

float Entity::GetMaxDy()
{
	int iX = int(std::ceil(x));
	int iXPlusW = int(std::ceil(x + width)) - 1;
	int iYPlusH = int(std::ceil(y + height));
	float maxDyB = 999;
	for(int by = iYPlusH / blockHeight; by < 28; by++)
	{
		for(int bx = iX / blockWidth; bx <= iXPlusW / blockWidth; bx++)
		{
			if(IsBlockSolid(game.mapManager.BlockTypeAt(bx, by)))
			{
				maxDyB = float(by * blockHeight) - height - y;
			}
			if(maxDyB != 999) break;
		}
		if(maxDyB != 999) break;
	}
	float maxDyE = 999;
	Entity *entities[20];
	int n = game.entitiesManager.SearchArea(x, y + height, width, 999, entities, 20);
	for(int i = 0; i < n; i++)
	{
		if(entities[i] == this) continue;
		if(!IsEntitySolid(entities[i])) continue;
		if(entities[i]->y - y - height < maxDyE) maxDyE = entities[i]->y - y - height;
	}
	if(maxDyB < maxDyE) return maxDyB;
	else return maxDyE;
}

float Entity::GetMinDx()
{
	int iX = int(std::floor(x));
	int iY = int(std::ceil(y));
	int iYPlusH = int(std::ceil(y + height)) - 1;
	float minDxB = -999;
	for(int bx = iX / blockWidth; bx >= 0; bx--)
	{
		for(int by = iY / blockHeight; by <= iYPlusH / blockHeight; by++)
		{
			if(IsBlockSolid(game.mapManager.BlockTypeAt(bx, by)))
			{
				minDxB = float((bx + 1) * blockWidth) - x;
			}
			if(minDxB != -999) break;
		}
		if(minDxB != -999) break;
	}
	float minDxE = -999;
	Entity *entities[20];
	int n = game.entitiesManager.SearchArea(x - 999, y, 999, height, entities, 20);
	for(int i = 0; i < n; i++)
	{
		if(entities[i] == this) continue;
		if(!IsEntitySolid(entities[i])) continue;
		if(entities[i]->x + entities[i]->width - x > minDxE) minDxE = entities[i]->x + entities[i]->width - x;
	}
	if(minDxB > minDxE) return minDxB;
	else return minDxE;
}

float Entity::GetMinDy()
{
	int iX = int(std::ceil(x));
	int iXPlusW = int(std::ceil(x + width)) - 1;
	int iY = int(std::floor(y));
	float minDyB = -999;
	for(int by = iY / blockHeight; by >= 0; by--)
	{
		for(int bx = iX / blockWidth; bx <= iXPlusW / blockWidth; bx++)
		{
			if(IsBlockSolid(game.mapManager.BlockTypeAt(bx, by)))
			{
				minDyB = float((by + 1) * blockHeight) - y;
			}
			if(minDyB != -999) break;
		}
		if(minDyB != -999) break;
	}
	float minDyE = -999;
	Entity *entities[20];
	int n = game.entitiesManager.SearchArea(x, y - 999, width, 999, entities, 20);
	for(int i = 0; i < n; i++)
	{
		if(entities[i] == this) continue;
		if(!IsEntitySolid(entities[i])) continue;
		if(entities[i]->y + entities[i]->height - y > minDyE) minDyE = entities[i]->y + entities[i]->height - y;
	}
	if(minDyB > minDyE) return minDyB;
	else return minDyE;
}

bool Entity::MoveSolid(float dx, float dy)
{
	float _x = x;
	float _y = y;
	if(dx > 0)
	{
		if(GetMaxDx() < dx) x += GetMaxDx();
		else x += dx;
	}
	if(dx < 0)
	{
		if(GetMinDx() > dx) x += GetMinDx();
		else x += dx;
	}
	if(dy > 0)
	{
		if(GetMaxDy() < dy) y += GetMaxDy();
		else y += dy;
	}
	if(dy < 0)
	{
		if(GetMinDy() > dy) y += GetMinDy();
		else y += dy;
	}
	if((x == _x) && (y == _y)) return false;
	return true;
}

void Entity::OnCreate()
{
}

bool Entity::IsBlockFloor(int b)
{
	return ((b & 2) == 0);
}

float Entity::GetFeetHeight()
{
	return 15;
}

bool Entity::CheckFloor(float &floorX, float &floorY)
{
	bool isOnFloor = false;
	float feetY = y + height - GetFeetHeight();
	for(int bx = x / 15; (bx * 15) < x + width - 1; bx++)
	{
		for(int by = (feetY / 15); (by * 15) < y + height - 1; by++)
		{
			if(by < 0) continue;
			if(IsBlockFloor(game.mapManager.BlockTypeAt(bx, by)))
			{
				isOnFloor = true;
				floorX = (bx * 15) + 7.5 - width * 0.5;
				floorY = (by * 15) + 7.5 - height * 0.5;
				break;
			}
			if(by == 28) break;
		}
		if(bx == 41) break;
	}
	return isOnFloor;
}

bool Entity::CheckFloor()
{
	float x, y;
	return CheckFloor(x, y);
}

bool Entity::WithinDistanceTo(Entity *other, float distance)
{
	float dx = (other->x + other->width * 0.5) - x - width * 0.5;
	float dy = (other->y + other->height * 0.5) - y - height * 0.5;
	if(dx * dx + dy * dy  < distance * distance) return true;
	return false;
}

int Entity::PlaySample(const SAMPLE *spl, int vol, int freq)
{
	int pan = ((x + (width * 0.5f)) / 630.0f) * 255.0f;
	if(pan < 0) pan = 0;
	if(pan > 255) pan = 255;
	return play_sample(spl, vol, pan, freq, 0);
}
