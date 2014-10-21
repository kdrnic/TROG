#ifndef ENTITY_H
#define ENTITY_H

#include <allegro.h>

#include <string>

class Entity
{
	public:
		bool pushBack;
		bool alive, persistent;
		float x, y, width, height;
		int layer;
		
		virtual bool Is(std::string what);
		virtual void Draw(BITMAP *bmp);
		virtual void Update();
		virtual void OnCollision(Entity *e);
		virtual void SetParameter(std::string p, std::string v);
		
		bool Collision(Entity *e);		
		bool Collision(int _x, int _y, int _w, int _h);
		
		Entity();
	protected:
		virtual bool IsEntitySolid(Entity *e);
		virtual bool IsBlockSolid(int b);
		bool MapCollision();
		void MoveToFreeSpot(int minX = 0, int minY = 0, int maxX = 630, int maxY = 420);
		float GetMaxDx();
		float GetMaxDy();
		float GetMinDx();
		float GetMinDy();
		bool MoveSolid(float dx, float dy);		
};

#endif