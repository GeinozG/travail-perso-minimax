#include "Minimax.h"

#include <iostream>
#include <assert.h>

Minimax::Minimax(Board & board, SquareType minimizerPlayer, SquareType maximizerPlayer, int searchDepth):
    m_board(board),
    m_minimizerPlayer(minimizerPlayer),
    m_maximizerPlayer(maximizerPlayer),
    m_searchDepth(searchDepth)
{
}

Minimax::~Minimax()
{

}

void Minimax::play()
{
    Vector2 bestMove;
    BufBoard currentPosition = m_board.getBufBoardCopy();
    std::cout << "Current position value: " <<
        minimax(
            currentPosition,
            bestMove,
            0,
            m_board.getMaxMoves(),
            MINUS_INFINITY,
            PLUS_INFINITY,
            m_maximizerPlayer) << std::endl;

    m_board.squarePlay(bestMove, m_maximizerPlayer);
}

std::vector<Vector2> Minimax::getMoves(BufBoard const& bufBoard)
{
    std::vector<Vector2> moves;

    for (int col = 0; col < BOARD_WIDTH; col++)
    {
        for (int line = BOARD_HEIGHT - 1; line >= 0; line--)
        {
            if (bufBoard.squares[line][col] == SquareType::Empty)
            {
                moves.push_back({ col, line });
                break;
            }
        }
    }

    return moves;
}

int Minimax::minimax(
    BufBoard const& position,
    Vector2 & bestMove,
    int depth,
    int maxMoves,
    int alpha,
    int beta,
    SquareType player)
{
    assert(player != SquareType::Empty);

    SquareType winner = m_board.isWin(position);

    if (depth == m_searchDepth || maxMoves == 0 || winner != SquareType::Empty)
    {
        return evaluatePosition(position, player);
    }

    std::vector<Vector2> possibleMoves = getMoves(position);
    BufBoard childPosition = position;

    if (player == m_maximizerPlayer)
    {
        int maxWeight = MINUS_INFINITY;

        for (Vector2 move : possibleMoves)
        {
            childPosition.squares[move.y][move.x] = player;

            int weight = minimax(childPosition, bestMove, depth + 1, maxMoves - 1, alpha, beta, m_minimizerPlayer);
            if (depth == 0 && weight > maxWeight) bestMove = move;
            maxWeight = std::max(weight, maxWeight);

            childPosition.squares[move.y][move.x] = SquareType::Empty;

            alpha = std::max(weight, alpha);
            if (beta <= alpha) return maxWeight;
        }

        return maxWeight;
    }
    else if (player == m_minimizerPlayer)
    {
        int minWeight = PLUS_INFINITY;

        for (Vector2 move : possibleMoves)
        {
            childPosition.squares[move.y][move.x] = player;

            int weight = minimax(childPosition, bestMove, depth + 1, maxMoves - 1, alpha, beta, m_maximizerPlayer);
            minWeight = std::min(weight, minWeight);

            childPosition.squares[move.y][move.x] = SquareType::Empty;

            beta = std::min(weight, beta);
            if (beta <= alpha) return minWeight;
        }

        return minWeight;
    }
}

int Minimax::evaluatePosition(BufBoard const& position, SquareType player)
{
    int weight = 0;

    for (int line = 0; line < BOARD_HEIGHT; line++)
    {
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            if (position.squares[line][col] == m_maximizerPlayer)
            {
                weight += m_evaluationTable[line][col];
            }
            else if (position.squares[line][col] == m_minimizerPlayer)
            {
                weight -= m_evaluationTable[line][col];
            }
        }
    }

    SquareType winner = m_board.isWin(position);
    if (winner == m_maximizerPlayer) weight += 100;
    else if (winner == m_minimizerPlayer) weight -= 100;

    return weight;
}
