#ifndef DEF_MINIMAX
#define DEF_MINIMAX

#include "Board.h"

const int PLUS_INFINITY = 9999;
const int MINUS_INFINITY = -9999;

class Minimax
{
public:
    Minimax(Board & board, SquareType minimizerPlayer, SquareType maximizerPlayer, int m_searchDepth);
    ~Minimax();

    void play();

private:
    int minimax(
        BufBoard const& position,
        Vector2 & bestMove,
        int depth,
        int maxMoves,
        int alpha,
        int beta,
        SquareType player
    );
    int evaluatePosition(BufBoard const& position, SquareType player);
    std::vector<Vector2> getMoves(BufBoard const& bufBoard);

    Board & m_board;
    const int m_evaluationTable[6][7] = {
        { 3, 4, 5, 7, 5, 4, 3 }, 
        { 4, 6, 8, 10,8, 6, 4 },
        { 5, 8, 11,13,11,8, 5 }, 
        { 5, 8, 11,13,11,8, 5 },
        { 4, 6, 8, 10,8, 6, 4 },
        { 3, 4, 5, 7, 5, 4, 3 }
    };

    SquareType m_minimizerPlayer;
    SquareType m_maximizerPlayer;
    const int m_searchDepth;
};

#endif
