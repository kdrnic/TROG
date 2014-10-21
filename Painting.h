#ifndef PAINTING_H
#define PAINTING_H

#include "EventEntity.h"

class Painting : public EventEntity
{
	public:
		static BITMAP *_sprite;
		void SetParameter(std::string p, std::string v);
		void Interact();

		void Draw(BITMAP *bmp);

		Painting();
		~Painting();
		static Entity *Create();
	private:
		int file;
		BITMAP *canvas;
};


#endif
