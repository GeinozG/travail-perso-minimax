#include "Board.h"

#include <iostream>
#include <assert.h>
#include "Mouse.h"

Board::Board(GraphicsManager const& graphics, int squareSize, float scale):
    m_graphics(graphics),
    m_squareSize(squareSize),
    m_scale(scale),
    m_maxMoves(BOARD_WIDTH * BOARD_HEIGHT)
{

}

Board::~Board()
{

}

void Board::load()
{
    m_graphics.loadTexture("assets/images/cross.png", m_texCross);
    m_graphics.loadTexture("assets/images/circle.png", m_texCircle);
    m_graphics.loadTexture("assets/images/empty.png", m_texEmpty);
}

Vector2 Board::mouseToSquare()
{
    int squareCol = float(Mouse::x) / m_squareSize / m_scale;
    int squareLine;
    for (int line = BOARD_HEIGHT - 1; line >= 0; line--)
    {
        if (getSquareType({ squareCol, line }) == SquareType::Empty)
        {
            squareLine = line;
            break;
        }
    }

    Vector2 square {
        squareCol,
        squareLine
    };

    return square;
}

BufBoard Board::getBufBoardCopy() const
{
    return m_bufBoard;
}

void Board::squarePlay(Vector2 square, SquareType squareType)
{
    assert(squareType != SquareType::Empty);
    assert(getSquareType(square) == SquareType::Empty);

    m_bufBoard.squares[square.y][square.x] = squareType;
    m_maxMoves--;
}

bool Board::mousePlay(SquareType squareType)
{
    assert(squareType != SquareType::Empty);

    if (Mouse::isLeftDown && !Mouse::wasLeftDown)
    {
        const Vector2 square = mouseToSquare();
        if (getSquareType(square) == SquareType::Empty)
        {
            squarePlay(square, squareType);

            return true;
        }
    }

    return false;
}

SquareType Board::isWin(BufBoard const& position) const
{
    std::vector<std::vector<SquareType>> cols = getColumns(position);
    std::vector<std::vector<SquareType>> lines = getLines(position);
    std::vector<std::vector<SquareType>> dias = getDiagonals(position);

    int occurence = 0;
    SquareType currentType;
    for (std::vector<SquareType> col : cols) {
        occurence = 0;
        currentType = SquareType::Empty;

        for (SquareType square : col)
        {
            if (square == SquareType::Empty)
            {
                occurence = 0;
                continue;
            }
            else if (square != currentType)
            {
                occurence = 1;
                currentType = square;
            }
            else if (square == currentType)
            {
                occurence++;
            }

            if (occurence == WIN_ROW)
            {
                return currentType;
            }
        }
    }

    for (std::vector<SquareType> line : lines) {
        occurence = 0;
        currentType = SquareType::Empty;

        for (SquareType square : line)
        {
            if (square == SquareType::Empty)
            {
                occurence = 0;
                continue;
            }
            else if (square != currentType)
            {
                occurence = 1;
                currentType = square;
            }
            else if (square == currentType)
            {
                occurence++;
            }

            if (occurence == WIN_ROW)
            {
                return currentType;
            }
        }
    }

    for (std::vector<SquareType> dia : dias) {
        occurence = 0;
        currentType = SquareType::Empty;

        for (SquareType square : dia)
        {
            if (square == SquareType::Empty)
            {
                occurence = 0;
                continue;
            }
            else if (square != currentType)
            {
                occurence = 1;
                currentType = square;
            }
            else if (square == currentType)
            {
                occurence++;
            }

            if (occurence == WIN_ROW)
            {
                return currentType;
            }
        }
    }
    
    return SquareType::Empty;
}

SquareType Board::getSquareType(Vector2 const& square) const
{
    assert(
        square.x < BOARD_WIDTH && square.x >=0 &&
        square.y < BOARD_HEIGHT && square.y >=0
    );

    return m_bufBoard.squares[square.y][square.x];
}

std::vector<std::vector<SquareType>> Board::getLines(BufBoard const& position) const
{
    std::vector<std::vector<SquareType>> lines = {
        { position.squares[0][0], position.squares[0][1], position.squares[0][2], position.squares[0][3], position.squares[0][4], position.squares[0][5], position.squares[0][6] },
        { position.squares[1][0], position.squares[1][1], position.squares[1][2], position.squares[1][3], position.squares[1][4], position.squares[1][5], position.squares[1][6] },
        { position.squares[2][0], position.squares[2][1], position.squares[2][2], position.squares[2][3], position.squares[2][4], position.squares[2][5], position.squares[2][6] },
        { position.squares[3][0], position.squares[3][1], position.squares[3][2], position.squares[3][3], position.squares[3][4], position.squares[3][5], position.squares[3][6] },
        { position.squares[4][0], position.squares[4][1], position.squares[4][2], position.squares[4][3], position.squares[4][4], position.squares[4][5], position.squares[4][6] },
        { position.squares[5][0], position.squares[5][1], position.squares[5][2], position.squares[5][3], position.squares[5][4], position.squares[5][5], position.squares[5][6] },
    };

    return lines;
}

std::vector<std::vector<SquareType>> Board::getColumns(BufBoard const& position) const
{
    std::vector<std::vector<SquareType>> cols = {
        { position.squares[0][0], position.squares[1][0], position.squares[2][0], position.squares[3][0], position.squares[4][0], position.squares[5][0], position.squares[6][0] },
        { position.squares[0][1], position.squares[1][1], position.squares[2][1], position.squares[3][1], position.squares[4][1], position.squares[5][1], position.squares[6][1] },
        { position.squares[0][2], position.squares[1][2], position.squares[2][2], position.squares[3][2], position.squares[4][2], position.squares[5][2], position.squares[6][2] },
        { position.squares[0][3], position.squares[1][3], position.squares[2][3], position.squares[3][3], position.squares[4][3], position.squares[5][3], position.squares[6][3] },
        { position.squares[0][4], position.squares[1][4], position.squares[2][4], position.squares[3][4], position.squares[4][4], position.squares[5][4], position.squares[6][4] },
        { position.squares[0][5], position.squares[1][5], position.squares[2][5], position.squares[3][5], position.squares[4][5], position.squares[5][5], position.squares[6][5] }
    };

    return cols;
}

std::vector<std::vector<SquareType>> Board::getDiagonals(BufBoard const& position) const
{
    // nombre de dia desc. = 6, avec n = 4
    // nombre de dia asc. = 6, avec n =4
    // total = 12
    
    // 2 dia de n=3 elements
    std::vector<std::vector<SquareType>> dias = {
        // desc.
        { position.squares[2][0], position.squares[3][1], position.squares[4][2], position.squares[5][3] },
        { position.squares[1][0], position.squares[2][1], position.squares[3][2], position.squares[4][3], position.squares[5][4] },
        { position.squares[0][0], position.squares[1][1], position.squares[2][2], position.squares[3][3], position.squares[4][4], position.squares[5][5] },
        { position.squares[0][1], position.squares[1][2], position.squares[2][3], position.squares[3][4], position.squares[4][5], position.squares[5][6] },
        { position.squares[0][2], position.squares[1][3], position.squares[2][4], position.squares[3][5], position.squares[4][6] },
        { position.squares[0][3], position.squares[1][4], position.squares[2][5], position.squares[3][6] },
        // asc.
        { position.squares[3][0], position.squares[2][1], position.squares[1][2], position.squares[0][3] },
        { position.squares[4][0], position.squares[3][1], position.squares[2][2], position.squares[1][3], position.squares[0][4] },
        { position.squares[5][0], position.squares[4][1], position.squares[3][2], position.squares[2][3], position.squares[1][4], position.squares[0][5] },
        { position.squares[5][1], position.squares[4][2], position.squares[3][3], position.squares[2][4], position.squares[1][5], position.squares[0][6] },
        { position.squares[5][2], position.squares[4][3], position.squares[3][4], position.squares[2][5], position.squares[1][6] },
        { position.squares[5][3], position.squares[4][4], position.squares[3][5], position.squares[2][6] }
    };

    return dias;
}

void Board::draw() const
{
    for (int line = 0; line < BOARD_HEIGHT; line++)
    {
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            SquareType type = getSquareType({ col, line });
            switch (type) {
            case SquareType::Human:
                m_graphics.drawTexture(m_texCircle, { int(col * m_squareSize * m_scale), int(line * m_squareSize * m_scale) }, m_scale);
                break;
            case SquareType::Computer:
                m_graphics.drawTexture(m_texCross, { int(col * m_squareSize * m_scale), int(line * m_squareSize * m_scale) }, m_scale);
                break;
            default:
                m_graphics.drawTexture(m_texEmpty, { int(col * m_squareSize * m_scale), int(line * m_squareSize * m_scale) }, m_scale);
                break;
            }
        }
    }
}

int Board::getMaxMoves()
{
    return m_maxMoves;
}
