#include "Game.h"

#include <iostream>
#include "Mouse.h"

Game::Game(int squareSize, int searchDepth, SquareType startingPlayer, float windowScale):
    m_window(squareSize * BOARD_WIDTH * windowScale, squareSize * BOARD_HEIGHT * windowScale),
    m_graphics(m_window),
    m_board(m_graphics, squareSize, windowScale),
    m_squareTurn(startingPlayer),
    m_minimax(m_board, SquareType::Human, SquareType::Computer, searchDepth)
{
}

Game::~Game()
{
}

void Game::loadAssets()
{
    m_board.load();
}

void Game::run()
{
	while (m_window.update())
    {
    	m_graphics.clearScreen();

        if (m_squareTurn == SquareType::Human && m_board.mousePlay(m_squareTurn))
        {
            SquareType winner = m_board.isWin(m_board.getBufBoardCopy());
            if (winner == SquareType::Human)
            {
                std::cout << "Win circle" << std::endl;
                m_squareTurn = SquareType::Empty;
                continue;
            }

            if (m_squareTurn == SquareType::Human) m_squareTurn = SquareType::Computer;
            else if (m_squareTurn == SquareType::Computer) m_squareTurn = SquareType::Human;
        }
        else if (m_squareTurn == SquareType::Computer)
        {
            m_minimax.play();
            SquareType winner = m_board.isWin(m_board.getBufBoardCopy());
            if (winner == SquareType::Computer)
            {
                std::cout << "Win cross" << std::endl;
                m_squareTurn = SquareType::Empty;
                continue;
            }

            m_squareTurn = SquareType::Human;
        }

        m_board.draw();

    	m_graphics.render();
    }
}
