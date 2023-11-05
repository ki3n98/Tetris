#pragma once

#include <assert.h>
#include <array>
#include <cstdlib>
#include <time.h>
#include <math.h>


#include "Game.h"
#include "raylib.h"
#include "Settings.h"


Game::Game(int width, int height,int fps, std::string title) 
	:
	board(settings::boardPosition,
		settings::boardWidthHeight,
		settings::cellSize,
		settings::padding),
	holdBlock(settings::holdPosition,
		settings::holdWidthHeight,
		settings::cellSize,
		settings::padding)
{
	assert(!IsWindowReady());					//if asssertion trigger: window is already open
	SetTargetFPS(fps); 
	InitWindow(width, height,title.c_str());
	tetrominoDeltaX = (float)tetrominos[STRAIGHT].getPos().getX();
	srand((unsigned)time(NULL));
	getNewTetromino();
	initHold();


}
void Game::initHold()
{
	for (auto& holdTetro : holds)
	{
		holdTetro.setPos({ holdBlock.getWidth() / 2 - holdTetro.getDimension() / 2 ,
							holdBlock.getHeight() / 2 - holdTetro.getDimension() / 2 });
	}
}

Game::~Game() noexcept 
{
	assert(IsWindowReady());				//if asssertion trigger: window is already open
	CloseWindow(); 
}

bool Game::gameShouldClose() const 
{
	return WindowShouldClose(); 
}

void Game::tick()
{
	BeginDrawing(); 
	update();
	EndDrawing(); 
}



void Game::applyGravity(Tetromino& tetromino)
{
	float deltaTime = GetFrameTime();
	tetrominoDeltaY += settings::gravity * deltaTime;
	tetromino.setPos({ tetromino.getPos().getX(), (int)round(tetrominoDeltaY) });
}

void Game::update()
{
	Tetromino& tetromino = tetrominos[activeTetromino];

	applyGravity(tetromino);
	inputHandle(tetromino);
	updateTetromino();
	updateShadow();
	score += board.deleteAllFullRows();
	displayText();
	draw();
}
void Game::gameOver()
{
	board.clear();
	prevScore = score; 
	score = 0; 
}
void swap(int& num1, int& num2)
{
	int temp = num1; 
	num1 = num2; 
	num2 = temp; 
}

void Game::inputHandle(Tetromino& tetromino)
{
	Tetromino tempTetro = tetromino;
	if (IsKeyPressed(KEY_E) || IsKeyPressed(KEY_W))
	{
		tetromino.rotateClockwise();
	}
	if (IsKeyPressed(KEY_Q))
	{
		tetromino.rotateCounterClockwise();
	}
	if (IsKeyPressed(KEY_A))
	{
		tempTetro.setPos(tetromino.getPos() - Vec2{1,0});
		if (!collideToBoard(tempTetro))
		{
			tetromino.setPos(tetromino.getPos() - Vec2{ 1,0 });
		}
		
	}
	if (IsKeyPressed(KEY_D))
	{

		tempTetro.setPos(tetromino.getPos() + Vec2{ 1,0 });
		if (!collideToBoard(tempTetro))
		{
			tetromino.setPos(tetromino.getPos() + Vec2{ 1,0 });
		}
		
	}
	if (IsKeyPressed(KEY_S)|| IsKeyDown(KEY_S))
	{
		tetrominoDeltaY += 0.5;
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		while (!collideToBoard(tetromino))
		{
			tetromino.setPos(tetromino.getPos() + Vec2{ 0,1 });
		}
	}
	if (IsKeyPressed(KEY_F))
	{
		updateHold();

	}
	if (IsKeyPressed(KEY_R))
	{
		board.clear();
		resetTetromino();
	}
}



bool Game::collideLeftBorder(const Tetromino& tetromino) const
{
	return (tetromino.getPos().getX() + tetromino.getStartX() <= 0);
}

bool Game::collideRightBorder(const Tetromino& tetromino) const
{
	return (tetromino.getPos().getX() >= board.getWidth() - tetromino.getEndX());
}

bool Game::collideBottom(const Tetromino& tetromino) const
{
	return tetromino.getPos().getY() + tetromino.getHeight() > board.getHeight();
}
bool Game::collideToBoard(Tetromino& tetromino)
{
	Vec2<int> tetrominoPos = tetromino.getPos();
	int dimension = tetromino.getDimension();

	if (collideBottom(tetromino)) //collide with the bottom of board
	{
		return true;
	}

	
	for (int y = 0; y < dimension; y++)	//collide with embeded cells
	{
		for (int x = 0; x < dimension; x++)
		{
			if (tetromino.cellExist({ x,y }) && 
				board.cellExist(tetrominoPos + Vec2{x,y}))
			{
				return true; 
			}
		}
	}

	return false;
}


void Game::embedTetromino(const Tetromino& tetromino)
{
	int dimension = tetromino.getDimension();  
	
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			if (tetromino.cellExist({ x,y }))
			{
				board.setCell(tetromino.getPos() + Vec2<int>{x, y}, tetromino.getColor());
			}
		}
	}
}

void Game::updateTetromino()
{
	Tetromino& tetromino = tetrominos[activeTetromino];
	while (tetromino.getPos().getX() + tetromino.getStartX() < 0)
	{
		tetromino.setPos(tetromino.getPos() + Vec2{ 1, 0 });
	}
	while (tetromino.getPos().getX() + tetromino.getEndX() > board.getWidth())
	{
		tetromino.setPos(tetromino.getPos() - Vec2{ 1, 0 });
	}

	if (collideToBoard(tetromino))
	{
		while (collideToBoard(tetromino))
		{
			tetromino.setPos({ tetromino.getPos() - Vec2{0,1} });
		}
 		if (tetromino.getPos().getY() <= 1)
		{
			gameOver();	//game over 
		}
		else
		{
			embedTetromino(tetromino);
		}
		resetTetromino();
	}

}
void Game::updateShadow()
{
	Tetromino& shadow = shadows[activeTetromino];
	shadow.setPos(tetrominos[activeTetromino].getPos());
	shadow.setRotation(tetrominos[activeTetromino].getRotation());

	while (!collideToBoard(shadow))
	{
		shadow.setPos(shadow.getPos() + Vec2{ 0,1 });
	}

	if (collideToBoard(shadow))
	{
		while (collideToBoard(shadow))
		{
			shadow.setPos({ shadow.getPos() - Vec2{0,1} });
		}
	}
}
void Game::updateHold()
{
	if (holdTetromino != -1)	//there is existing hold block
	{
		tetrominos[holdTetromino].setPos(tetrominos[activeTetromino].getPos());
		swap(activeTetromino, holdTetromino);
	}
	else //no hold block
	{
		holdTetromino = activeTetromino;
		Vec2<int> currentPos = tetrominos[activeTetromino].getPos();
		resetTetromino();
		tetrominos[activeTetromino].setPos(currentPos);
	}
}
void Game::draw()
{
	ClearBackground(BLACK); 
	board.draw(); 
	tetrominos[activeTetromino].draw();
	shadows[activeTetromino].draw(Color{255,255,255,50});
	holdBlock.draw();
	if (holdTetromino != -1)
	{
		holds[holdTetromino].draw();
	}
}

void Game::displayText()
{
	DrawText(TextFormat("Current Score : %04i\nPrevious Score: %04i", score,prevScore), 10, 100, 20, WHITE);
	DrawText(TextFormat("AD - move\nSpace - place bottom\nW - rotate\nF - Hold\nR - Reset"), 10, 180, 20, WHITE);
}

void Game::getNewTetromino()
{
	activeTetromino =rand() % 7; 
}

void Game::resetTetromino()
{
	tetrominos[activeTetromino].reset();
	tetrominoDeltaY = 0;
	tetrominoDeltaX = (float)tetrominos[activeTetromino].getPos().getX();
	getNewTetromino();
}
