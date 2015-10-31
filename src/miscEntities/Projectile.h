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
		void OnPlayer();
		void OnEnemy(Entity *e);
		void OnSolid(Entity *e);
		void OnMapCollision(bool isCollisionAtBirth);
		
		bool birthCollision;
};

#endif