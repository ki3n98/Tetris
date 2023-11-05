#include "Tetromino.h"


Tetromino::Tetromino(const bool* shape, const int* height, const int* startX, const int* endX, int dimension, Color color, const Board& board)
	:
	shape(shape),
	height(height),
	startX(startX),
	endX(endX),
	dimension(dimension),
	color(color),
	boardPos({ board.getWidth() / 2 - dimension / 2,0 }),
	board(board),
	currentRotation(Rotation::UP)
{
}



Vec2<int> Tetromino::getPos() const
{
	return boardPos;
}

int Tetromino::getDimension() const
{
	return dimension;
}

Color Tetromino::getColor() const
{
	return color;
}

Tetromino::Rotation Tetromino::getRotation() const
{
	return currentRotation;
}

int Tetromino::getHeight() const
{
	return height[(int)currentRotation];
}

int Tetromino::getStartX() const
{
	return startX[(int)currentRotation];
}

int Tetromino::getEndX() const
{
	return endX[(int)currentRotation];
}


void Tetromino::setPos(Vec2<int>newPos)
{
	boardPos = newPos; 
}

void Tetromino::setRotation(const Rotation inRotation)
{
	currentRotation = inRotation; 
}

void Tetromino::reset()
{
	boardPos = { board.getWidth() / 2 - dimension / 2,0 };
	currentRotation = Rotation::UP;
}

void Tetromino::rotateClockwise()
{
	currentRotation = Rotation((int(currentRotation)+1) % 4); 
}

void Tetromino::rotateCounterClockwise()
{
	if (currentRotation == Rotation::UP)
	{
		currentRotation = Rotation::LEFT;
	}
	else
	{
		currentRotation = Rotation(int(currentRotation) - 1);
	}
}

bool Tetromino::cellExist(const Vec2<int>& position) const
{
	bool cell = false;
	switch (currentRotation)
	{
	case Tetromino::Rotation::UP:
		cell = shape[position.getY() * dimension + position.getX()];
		break;
	case Tetromino::Rotation::RIGHT:
		cell = shape[dimension * (dimension - 1) - dimension * position.getX() + position.getY()];
		break;
	case Tetromino::Rotation::DOWN:
		cell = shape[(dimension * dimension - 1) - dimension * position.getY() - position.getX()];
		break;
	case Tetromino::Rotation::LEFT:
		cell = shape[dimension - 1 + dimension * position.getX() - position.getY()];
		break;
	default:
		break;
	}
	return cell;
}


void Tetromino::draw() const
{
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			if (cellExist({x,y}))
			{
				board.drawCell(boardPos + Vec2<int>{x, y}, color);
			}

		}
	}
}

void Tetromino::draw(Color inColor) const
{
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			if (cellExist({ x,y }))
			{
				board.drawCell(boardPos + Vec2<int>{x, y}, inColor);
			}

		}
	}

}
