#pragma once


#include "raylibCpp.h"
#include "Board.h"



class Tetromino
{
public:
	enum class Rotation
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};
public:
	Tetromino(const bool* shape, const int* height, const int* startX,const int* endX,int dimension, Color color, const Board& board);

	Vec2<int> getPos() const;
	int getDimension() const; 
	Color getColor() const; 
	Rotation getRotation() const;
	int getHeight() const; 
	int getStartX() const; 
	int getEndX() const; 
	
	bool cellExist(const Vec2<int>& position) const; 
	void setPos(Vec2<int>newPos);
	void setRotation(const Rotation inRotation); 
	void reset(); 

	void rotateClockwise();
	void rotateCounterClockwise();
	void draw() const; 
	void draw(Color color) const;

private:
	Vec2<int> boardPos; 
	Rotation currentRotation; 
	const int dimension;
	const Color color; 
	const Board& board; 
	const int* height; 
	const bool* shape;
	const int* startX; 
	const int* endX;

};

class Straight : public Tetromino
{
public:
	Straight(const Board& board)
		:
		Tetromino(shape,height, startX,endX,dimension,color,board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr  bool shape[] =  { 0,0,0,0,
										1,1,1,1,
										0,0,0,0,
										0,0,0,0 }; 
	static constexpr int height[] = { 2,4,3,4 };
	static constexpr int startX[] = { 0,2,0,1 };
	static constexpr int endX[]   = { 4,3,4,2 };

	static constexpr int dimension = 4; 
	static constexpr Color color = SKYBLUE; 
};

class Square: public Tetromino
{
public:
	Square(const Board& board)
		:
		Tetromino(shape, height, startX, endX, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr  bool shape[] =  { 1,1,
										1,1 };
	static constexpr int height[] = { 2,2,2,2 };
	static constexpr int startX[] = { 0,0,0,0 };
	static constexpr int endX[] = { 2,2,2,2 };
	static constexpr int dimension = 2;
	static constexpr Color color = YELLOW;
};

class Tee: public Tetromino
{
public:
	Tee(const Board& board)
		:
		Tetromino(shape, height, startX, endX, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr  bool shape[] =  { 0,1,0,
										1,1,1,
										0,0,0 };
	static constexpr int height[] = { 2,3,3,3 };
	static constexpr int startX[] = { 0,1,0,0 };
	static constexpr int endX[] = { 3,3,3,2 };
	static constexpr int dimension = 3;
	static constexpr Color color = MAGENTA;
};

class Jay : public Tetromino
{
public:
	Jay(const Board& board)
		:
		Tetromino(shape, height, startX, endX, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr  bool shape[] = { 1,0,0,
										1,1,1,
										0,0,0 };
	static constexpr int height[] = { 2,3,3,3 };
	static constexpr int startX[] = { 0,1,0,0 };
	static constexpr int endX[] = { 3,3,3,2 };
	static constexpr int dimension = 3;
	static constexpr Color color = DARKBLUE;
};

class El : public Tetromino
{
public:
	El(const Board& board)
		:
		Tetromino(shape, height, startX, endX, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr  bool shape[] = { 0,0,1,
										1,1,1,
										0,0,0 };
	static constexpr int height[] = { 2,3,3,3 };
	static constexpr int startX[] = { 0,1,0,0 };
	static constexpr int endX[] = { 3,3,3,2 };

	static constexpr int dimension = 3;
	static constexpr Color color = ORANGE;
};
class SkewS : public Tetromino
{
public:
	SkewS(const Board& board)
		:
		Tetromino(shape, height, startX, endX, dimension, color, board)

	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr  bool shape[] =  { 0,1,1,
										1,1,0,
										0,0,0 };
	static constexpr int height[] = { 2,3,3,3 };
	static constexpr int startX[] = { 0,1,0,0 };
	static constexpr int endX[] = { 3,3,3,2 };

	static constexpr int dimension = 3;
	static constexpr Color color = GREEN;
};
class SkewZ : public Tetromino
{
public:
	SkewZ(const Board& board)
		:
		Tetromino(shape, height, startX, endX, dimension, color, board)

	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension);
	}
private:
	static constexpr  bool shape[] = { 1,1,0,
										0,1,1,
										0,0,0 };
	static constexpr int height[] = { 2,3,3,3 };
	static constexpr int startX[] = { 0,1,0,0 };
	static constexpr int endX[] = { 3,3,3,2 };

	static constexpr int dimension = 3;
	static constexpr Color color = RED;
};


