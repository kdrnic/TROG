#ifndef PLAYER_H
#define PLAYER_H

#include "SpriteEntity.h"
#include "Item.h"

class Player : public SpriteEntity
{
	public:
		Item *equippedItems[2];
		int health;
		int maxHealth;
		int gold;
		bool dead;
		float speedX, speedY;

		bool Is(std::string what);
		void Draw(BITMAP *bmp);
		void Update();

		void OnHit(int damage);
		void OnHit(int hx, int hy, int hw, int hh, int damage);
		void Heal(int h);

		bool Attack(int frame, int damage, int animSpeed = 5);

		Player();
		~Player();
	protected:
		bool IsEntitySolid(Entity *e);

	private:
		float maxSpeed;
		float accel;
		
		bool falling;
		float lastFloorX, lastFloorY;
		int fallAnimSpeed;
		int fallDamage, fallRespawnHit;

		int walkAnimSpeed, deadAnimSpeed;
		int invulnerabilityCounter;
		int blinkingHz;
		int invulnerabilityTime;
		int hitJump;
		bool isAttacking;
		bool hasHitEnemy;
		int attackDamage;
		bool movedLastFrame;
};

#endif
