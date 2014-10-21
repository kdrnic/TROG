#include "EntitiesManager.h"

void EntitiesManager::Add(Entity *e)
{
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

void EntitiesManager::Draw(BITMAP *bmp)
{
	entities.sort(EntityCompareZ);
	for(std::list<Entity *>::iterator i = entities.begin(); i != entities.end(); i++)
	{
		if((*i)->alive == false) continue;
		(*i)->Draw(bmp);
	}
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