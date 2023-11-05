
#include "raylibCpp.h"
#include <assert.h>

void raycpp::DrawRectangle(const Vec2<int>& pos, const Vec2<int>& widthHeight, Color color)
{
	DrawRectangle(pos.getX(), pos.getY(), widthHeight.getX(), widthHeight.getY(), color);
}

void raycpp::DrawRectangleLinesEx(Vec2<int> pos, Vec2<int>widthHeight, float lineThick, Color color)
{
	DrawRectangleLinesEx({(float)pos.getX(),(float)pos.getY(),(float)widthHeight.getX(),(float)widthHeight.getY()}, lineThick, color);
}
