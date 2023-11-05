#pragma once
#include "Vec2.h"

namespace settings
{
	//	inline turn variable into external linkage. So we only use the same amount of memory for these const.
	//	constepxr allow object to be create at compile time 
	// 
	// 
	//window settings
	inline constexpr int screenWidth = 800; 
	inline constexpr int screenHeight = 600;
	inline constexpr int fps = 60;


	//Board settings
	inline constexpr int cellSize = 23;
	inline constexpr int padding = 2;
	
	inline constexpr Vec2<int> boardPosition{250,70};
	inline constexpr Vec2<int> boardWidthHeight{ 10,20};
	inline constexpr Vec2<int> holdPosition{ 550,100 };
	inline constexpr Vec2<int> holdWidthHeight{ 6,6 };
	inline constexpr float gravity = 0.5;

}
