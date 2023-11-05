#pragma once
#include "Board.h"


Board::Cell::Cell() 
	:
	bExits(false),
	c(BLACK)
{
}

Board::Cell::Cell(const Cell& rhs)
{
	bExits = rhs.bExits;
	c = rhs.c;
}

void Board::Cell::setColor(Color color)
{
	c = color; 
	bExits = true; 
}

void Board::Cell::remove()
{
	bExits = false; 
}

bool Board::Cell::exist() const
{
	return bExits;
}

Color Board::Cell::getColor() const
{
	return c;
}

Board::Board(Vec2<int> screenPos, Vec2<int>widthHeight, int cellSize,int padding)
	:
	screenPos(screenPos),
	width(widthHeight.getX()),
	height(widthHeight.getY()),
	cellSize(cellSize),
	padding(padding)
{
	cells.resize(width * height); 
}

void Board::setCell(Vec2<int>pos, Color c)
{
	cells[pos.getY() * width + pos.getX()].setColor(c);
}

void Board::drawCell(Vec2<int>pos) const
{
	Color c = cells[pos.getY() * width + pos.getX()].getColor();
	drawCell(pos, c); 
}


void Board::drawCell(Vec2<int> pos, Color color) const
{
	Color c = cells[pos.getY() * width + pos.getX()].getColor();
	Vec2<int>topLeft = screenPos + padding + (pos * cellSize);

	raycpp::DrawRectangle(topLeft, Vec2{ cellSize,cellSize } - padding, color);
}

void Board::drawBorder() const
{
	raycpp::DrawRectangleLinesEx(screenPos - (cellSize / 2),
		Vec2{ width * cellSize,height * cellSize }+(cellSize),
		cellSize/2,
		WHITE);
}

void Board::draw() const
{
	for (int iY = 0; iY < height; iY++) 
	{
		for (int iX = 0; iX < width; iX++)
		{
			if (cellExist(Vec2{ iX,iY }))
			{
				drawCell({ iX, iY });
			}
		}
	}
	drawBorder(); 
}

void Board::deleteRow(int y)
{
	for (int iX=0; iX < width; iX++)
	{
		cells[y * width + iX].remove();
	}
}

void Board::deleteEmptyRows()
{
	int j = height-1; 
	for (int i = j; i > 0; i--)
	{
		if (isEmptyRow(i))
		{ 
			while (isEmptyRow(j) && j > 0) //find the next non-empty row
			{
				j--;
			}
			swapRow(i, j);
		}

		if (j <= 0) return; 

		j--;
	}
}

void Board::clear()
{
	for (int i = 0; i < width * height; i++)
	{
		cells[i].remove();
	}
}

void Board::swapRow(int row1, int row2)
{
	Cell tempCell; 
	for (int i = 0; i < width; i++)
	{
		tempCell = cells[row1 * width + i]; 
		cells[row1 * width + i] = cells[row2 * width + i];
		cells[row2 * width + i] = tempCell;
	}
}





int Board::deleteAllFullRows()
{
	int score = 0; 
	for (int iY = 0; iY < height; iY++)
	{
		if (isFullRow(iY))
		{
			score += 10; 
			deleteRow(iY);
		}
	}
	deleteEmptyRows();

	return score; 
}



bool Board::cellExist(Vec2<int> pos) const
{
	if (pos.getY() < 0 || pos.getY()> height)
		return false; 
	return cells[pos.getY()*width + pos.getX()].exist();
}

bool Board::isFullRow(int y) const
{
	for (int iX = 0; iX < width; iX++)
	{
		if (!cellExist({ iX,y }))
		{
			return false; 
		}
	}
	return true;
}

bool Board::isEmptyRow(int y) const
{
	for (int iX = 0; iX < width; iX++)
	{
		if (cellExist({ iX,y }))
		{
			return false;
		}
	}
	return true;
}

int Board::getWidth() const
{
	return width;
}

int Board::getHeight() const
{
	return height;
}
