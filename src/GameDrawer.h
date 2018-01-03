#ifndef GAMEDRAWER_H
#define GAMEDRAWER_H

struct BITMAP;

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