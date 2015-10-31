#ifndef ARROW_H
#define ARROW_H

#include "Entity.h"

class Arrow : public Entity
{
	public:
		static BITMAP *_sprite;
		void Draw(BITMAP *bmp);
		void OnCollision(Entity *e);
		void Update();
		
		Arrow(float _x, float _y, float a);
	private:
		BITMAP *sprite;
		float angle;
		float speed;
		int damage;
		int centerX, centerY;
};

#endif