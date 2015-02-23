#ifndef GAMEDRAWER_H
#define GAMEDRAWER_H

#include <allegro.h>

class GameDrawer
{
	public:
		virtual void BeginDrawing(BITMAP *dest, int x, int y);
		virtual void DrawRow();
		virtual void FinishDrawing();
	protected:
		int topLeftX, topLeftY;
		int rowAt;
		BITMAP *destBitmap;
};

#endif