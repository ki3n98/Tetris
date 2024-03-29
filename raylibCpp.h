#pragma once
#include <raylib.h>
#include "Vec2.h"



namespace raycpp
{
	void DrawRectangle(const Vec2<int>& pos, const Vec2<int>& widthHeight, Color color);
	void DrawRectangleLinesEx(Vec2<int> pos,Vec2<int>widthHeight, float lineThick, Color color);
}