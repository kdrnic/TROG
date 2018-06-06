#ifndef ENTITY_H
#define ENTITY_H

struct BITMAP;
struct SAMPLE;

#include <string>

class Entity
{
	public:
		unsigned int mapId;
		
		bool ignorePos;
		bool pushBack;
		bool alive, persistent;
		float x, y, width, height;
		int layer;
		
		virtual bool Is(std::string what);
		virtual void Draw(BITMAP *bmp);
		virtual void Update();
		virtual void OnCollision(Entity *e);
		virtual void SetParameter(std::string p, std::string v);
		virtual void OnCreate();
		
		bool Collision(Entity *e);
		bool Collision(int _x, int _y, int _w, int _h);
		
		bool WithinDistanceTo(Entity *other, float distance);
		
		int PlaySample(const SAMPLE *spl, int vol = 255, int freq = 1000);
		int PlaySample(const char *name, int vol = 255, int freq = 1000);

		void GetCenter(float &x, float &y);
		void GetCenter(int &x, int &y);
		
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
		
		virtual bool IsBlockFloor(int b);
		virtual float GetFeetHeight();
		bool CheckFloor(float &floorX, float &floorY);
		bool CheckFloor();
};

#endif
