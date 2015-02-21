#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <list>

#include "Entity.h"

class EntitiesManager
{
	public:
		void Add(Entity *e);
		
		void RemoveDead();
		void RemoveNonPersistent();
		void Clear();
		
		void Update();
		void Draw(BITMAP *bmp);
		
		int SearchArea(int x, int y, int width, int height, Entity **entities, int maxEntities);
		int Count(std::string w);
		int Count();
	private:
		std::list<Entity *> entities;
};

#endif