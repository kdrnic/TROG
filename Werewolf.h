#ifndef WEREWOLF_H
#define WEREWOLF_H

#include "Enemy.h"

class Werewolf : public Enemy
{
	public:
		static BITMAP *_sprite;
		
		void Update();
		void OnHit(int damage);
		void OnHit(int hx, int hy, int hw, int hh, int damage);
		
		Werewolf();
		
		static Entity *Create();
	private:
		bool isTransforming;
		bool isWerewolf;
		int transformationSpeed;
		int transformationCountdown, transformationTimeBase, transformationTimePlus;
		
		float humanSpeed;
		int humanAnimSpeed;
		bool humanWalking;
		int humanWalkTime;
		int humanWalkCounter;
		int humanAgitation;
		
		float werewolfSpeed;
		int werewolfAnimSpeed;
		int werewolfTurnTime;
		
		bool isAttacking, isPreparing;
		int attackCountdown, attackDelay, attackDamage, attackSpeed;
		bool hasHit;
};

#endif