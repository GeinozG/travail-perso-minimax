#ifndef DEF_BOARD
#define DEF_BOARD

#include <vector>
#include "GraphicsManager.h"

const int BOARD_WIDTH = 7;
const int BOARD_HEIGHT = 6;
const int WIN_ROW = 4;

enum class SquareType
{
    Empty,
    Human,
    Computer
};

struct BufBoard
{
    SquareType squares[BOARD_HEIGHT][BOARD_WIDTH] {
        { SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty },
        { SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty },
        { SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty },
        { SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty },
        { SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty },
        { SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty, SquareType::Empty }
    };
};

class Board
{
public:
    Board(GraphicsManager const& graphics, int squareSize, float scale);
    ~Board();

    void load();

    BufBoard getBufBoardCopy() const;
    void squarePlay(Vector2 square, SquareType squareType);
    bool mousePlay(SquareType squareType);
    SquareType isWin(BufBoard const& position) const;
    void draw() const;
    SquareType getSquareType(Vector2 const& square) const;
    int getMaxMoves();

private:
    Vector2 mouseToSquare();

    std::vector<std::vector<SquareType>> getLines(BufBoard const& position) const;
    std::vector<std::vector<SquareType>> getColumns(BufBoard const& position) const;
    std::vector<std::vector<SquareType>> getDiagonals(BufBoard const& position) const;

	GraphicsManager const& m_graphics;

    BufBoard m_bufBoard;

    int m_squareSize;
    float m_scale;
    int m_maxMoves;

    Texture m_texCircle;
    Texture m_texCross;
    Texture m_texEmpty;
};

#endif
