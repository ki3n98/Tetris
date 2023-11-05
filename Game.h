#pragma once
#include <string>
#include "Board.h"
#include "Tetromino.h"

class Game {
private:
	enum TETROMINO
	{
		STRAIGHT,
		SQUARE,
		TEE,
		JAY,
		EL,
		SKEWS,
		SKEWZ
	};
public:
	Game(int width, int height,int fps, std::string title); 
	Game(const Game& other) = delete;				 //don't allow copy constructor
	Game& operator=(const Game& other) = delete; 
	~Game() noexcept;								//avoid stack unwinding
	bool gameShouldClose() const; 
	void tick(); 
private:
	void update();
	void gameOver();
	void initHold(); 
	void inputHandle(Tetromino& tetromino);
	bool collideToBoard(Tetromino& tetromino);
	void applyGravity(Tetromino& tetromino); 
	void updateTetromino();
	void updateShadow(); 
	void updateHold();
	bool collideLeftBorder(const Tetromino& tetromino) const;
	bool collideRightBorder(const Tetromino& tetromino) const;
	bool collideBottom(const Tetromino& tetromino) const;
	void embedTetromino(const Tetromino& tetromino); 
	void draw();
	void displayText();
	void getNewTetromino();
	void resetTetromino();

	int score = 0;
	int prevScore = 0; 
	int activeTetromino = STRAIGHT; 
	int holdTetromino = -1; 
	float tetrominoDeltaY = 0; 
	float tetrominoDeltaX = 0; 

	Board board;
	Board holdBlock; 
	

	Tetromino tetrominos[7] = {Straight(board),
								Square(board),
								Tee(board),
								Jay(board),
								El(board),
								SkewS(board),
								SkewZ(board) };

	Tetromino shadows[7] = { Straight(board),
							Square(board),
							Tee(board),
							Jay(board),
							El(board),
							SkewS(board),
							SkewZ(board) };

	Tetromino holds[7] = { Straight(holdBlock),
						Square(holdBlock),
						Tee(holdBlock),
						Jay(holdBlock),
						El(holdBlock),
						SkewS(holdBlock),
						SkewZ(holdBlock) };






};





