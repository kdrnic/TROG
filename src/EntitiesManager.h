#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H

#include <list>
#include <string>

class Entity;
#include "GameDrawer.h"

class EntitiesManager : public GameDrawer
{
	public:
		void Add(Entity *e);

		void RemoveDead();
		void RemoveNonPersistent();
		void Clear();

		void Update();

		void BeginDrawing(BITMAP *dest, int x, int y);
		void DrawRow();
		void FinishDrawing();

		int SearchArea(int x, int y, int width, int height, Entity **entities, int maxEntities);
		int Count(std::string w);
		int Count();
		int FilterEntities(std::string what, Entity **entities, int maxEntities);
		Entity *GetByMapId(int mapId);
	private:
		std::list<Entity *> entities;
		std::list<Entity *>::iterator drawIt;
};

#endif
