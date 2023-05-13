#ifndef DEF_GAME
#define DEF_GAME

#include "Window.h"
#include "GraphicsManager.h"
#include "Board.h"
#include "Minimax.h"

class Game
{
public:
	Game(int squareSize, int searchDepth, SquareType startingPlayer, float windowScale);
	~Game();

	void loadAssets();
	void run();

private:
	Window m_window;
	GraphicsManager m_graphics;
    Board m_board;
    SquareType m_squareTurn;
    Minimax m_minimax;
};

#endif
