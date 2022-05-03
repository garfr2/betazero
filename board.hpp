#include "bitboard.hpp"

#define BB_PER_BOARD 12

enum class Team
{
    Black,
    White
};

enum class Piece
{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
};

class Board
{
public:
    BitBoard boards[BB_PER_BOARD];
    BitBoard white_board, black_board;

    BitBoard &get_board(Team team, Piece piece)
    {
        return *(&boards[(int) team * 6 + (int) piece]);
    }

    Board();
};