#pragma once
#include <vector>

#include "raylibCpp.h"

class Board 
{
private:
	class Cell 
	{
		public:
			Cell(); 
			Cell(const Cell& rhs);
			void setColor(Color color); 
			void remove(); 
			bool exist() const; 
			Color getColor() const; 
		private:
			bool bExits; 
			Color c; 
	};

public:
	Board(Vec2<int> screenPos,Vec2<int>widthHeight, int cellSize, int padding); 
	void setCell(Vec2<int>pos, Color c); 
	void drawCell(Vec2<int>pos) const; 
	void drawCell(Vec2<int>pos,Color color) const;
	void drawBorder() const; 
	void draw() const; 
	void deleteEmptyRows();
	void clear();

	bool cellExist(Vec2<int>pos) const;
	bool isFullRow(int y) const; 
	bool isEmptyRow(int y) const; 
	int getWidth() const; 
	int getHeight() const; 
	int deleteAllFullRows();
private:
	std::vector<Cell> cells; 

	const int width; 
	const int height; 
	const int cellSize; 
	const int padding; 

	Vec2<int>screenPos; 


	void deleteRow(int y);
	void swapRow(int row1, int row2);




};