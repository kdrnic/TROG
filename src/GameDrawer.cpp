#include "GameDrawer.h"

void GameDrawer::BeginDrawing(BITMAP *dest, int x, int y)
{
	destBitmap = dest;
	topLeftX = x;
	topLeftY = y;
	rowAt = -1;
}

void GameDrawer::DrawRow()
{
	rowAt++;
}

void GameDrawer::FinishDrawing()
{
}