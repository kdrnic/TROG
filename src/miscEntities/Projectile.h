#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "SpriteEntity.h"

class Projectile : public SpriteEntity
{
	public:
		void OnCollision(Entity *e);
		void Update();
		
		void SetSpeed(int _orientation, float speed);
		
		Projectile();
		
		float speedX, speedY;
		int damage;
	private:
		virtual void OnPlayer();
		virtual void OnEnemy(Entity *e);
		virtual void OnSolid(Entity *e);
		virtual void OnMapCollision(bool isCollisionAtBirth);
		
		bool birthCollision;
};

#endif