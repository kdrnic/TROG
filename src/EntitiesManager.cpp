#include "EntitiesManager.h"
#include "Entity.h"

void EntitiesManager::Add(Entity *e)
{
	e->OnCreate();
	entities.push_back(e);
}

void EntitiesManager::RemoveDead()
{
	std::list<Entity *>::iterator i = entities.begin();
	while(i != entities.end())
	{
		if((*i)->alive == false)
		{
			delete (*i);
			entities.erase(i++);
		}
		else i++;
	}
}

void EntitiesManager::RemoveNonPersistent()
{
	std::list<Entity *>::iterator i = entities.begin();
	while(i != entities.end())
	{
		if((*i)->persistent == false)
		{
			delete (*i);
			entities.erase(i++);
		}
		else i++;
	}
}

void EntitiesManager::Clear()
{
	std::list<Entity *>::iterator i = entities.begin();
	while(i != entities.end())
	{
		delete (*i);
		entities.erase(i++);
	}
}

void EntitiesManager::Update()
{
	for(std::list<Entity *>::iterator i = entities.begin(); i != entities.end(); i++)
	{
		if((*i)->alive == false) continue;
		(*i)->Update();
		for(std::list<Entity *>::iterator j = entities.begin(); j != entities.end(); j++)
		{
			if((*j)->alive == false) continue;
			if(*i != *j)
			{
				if((*i)->Collision(*j)) (*i)->OnCollision(*j);
			}
			if((*i)->alive == false) break;
		}
	}
}

bool EntityCompareZ(Entity *first, Entity *second)
{
	if(first->layer != second->layer) return (first->layer < second->layer);
	return (first->y + first->height < second->y + second->height);
}

void EntitiesManager::BeginDrawing(BITMAP *dest, int x, int y)
{
	GameDrawer::BeginDrawing(dest, x, y);

	entities.sort(EntityCompareZ);
	drawIt = entities.begin();
	while((drawIt != entities.end()) && ((*drawIt)->layer < 0))
	{
		if((*drawIt)->alive)
		{
			(*drawIt)->Draw(destBitmap);
		}
		drawIt++;
	}
}

void EntitiesManager::DrawRow()
{
	GameDrawer::DrawRow();

	while((drawIt != entities.end()) && ((*drawIt)->y + (*drawIt)->height <= (rowAt + 1) * 30) && ((*drawIt)->layer < 1))
	{
		if((*drawIt)->alive)
		{
			(*drawIt)->Draw(destBitmap);
		}
		drawIt++;
	}
}

void EntitiesManager::FinishDrawing()
{
	while(drawIt != entities.end())
	{
		if((*drawIt)->alive)
		{
			(*drawIt)->Draw(destBitmap);
		}
		drawIt++;
	}

	GameDrawer::FinishDrawing();
}

int EntitiesManager::SearchArea(int x, int y, int width, int height, Entity **foundEntities, int maxEntities)
{
	int j = 0;
	for(std::list<Entity *>::iterator i = entities.begin(); i != entities.end(); i++)
	{
		if(j == maxEntities) break;
		if((*i)->alive == false) continue;
		if((*i)->Collision(x, y, width, height))
		{
			foundEntities[j] = *i;
			j++;
		}
	}
	return j;
}

int EntitiesManager::Count(std::string w)
{
	int j = 0;
	for(std::list<Entity *>::iterator i = entities.begin(); i != entities.end(); i++)
	{
		if((*i)->Is(w))
		{
			if((*i)->alive) j++;
		}
	}
	return j;
}

int EntitiesManager::Count()
{
	return entities.size();
}

int EntitiesManager::FilterEntities(std::string what, Entity **foundEntities, int maxEntities)
{
	int j = 0;
	for(std::list<Entity *>::iterator i = entities.begin(); i != entities.end(); i++)
	{
		if(j == maxEntities) break;
		if((*i)->alive == false) continue;
		if((*i)->Is(what))
		{
			foundEntities[j] = *i;
			j++;
		}
	}
	return j;
}

Entity *EntitiesManager::GetByMapId(int mapId)
{
	for(std::list<Entity *>::iterator i = entities.begin(); i != entities.end(); i++)
	{
		if((*i)->alive == false) continue;
		if((*i)->persistent) continue;
		if((*i)->mapId == mapId) return (*i);
	}
	return 0;
}