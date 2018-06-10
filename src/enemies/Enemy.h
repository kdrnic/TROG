#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "SpriteEntity.h"

class Enemy : public SpriteEntity
{
	public:
		typedef Entity(*(*CreateDropFunction)());
		
		int health;
		float hitJump;
		
		virtual bool Is(std::string what);
		virtual void Update();
		virtual void Die();
		virtual void OnHit(int damage);
		virtual void OnHit(int hx, int hy, int hw, int hh, int damage);
		
		virtual const char *GetHurtSound();
		virtual const char *GetDyingSound();
		
		virtual std::vector<CreateDropFunction> PossibleDrops();		
		void Drop();
		
		Enemy();
		
	protected:
		int noDropChance;
		
		bool MoveSmart(float dx, float dy);
		bool MoveSmart(float speed);
};

#endif