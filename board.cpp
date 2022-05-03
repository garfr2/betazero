#include "board.hpp"

Board::Board()
{
    get_board(Team::White, Piece::Pawn).bits   = 0x00FF000000000000ULL;
    get_board(Team::Black, Piece::Pawn).bits   = 0x000000000000FF00ULL;
    get_board(Team::White, Piece::Rook).bits   = 0x8100000000000000ULL;
    get_board(Team::Black, Piece::Rook).bits   = 0x0000000000000081ULL;
    get_board(Team::White, Piece::Knight).bits = 0x4200000000000000ULL;
    get_board(Team::Black, Piece::Knight).bits = 0x0000000000000042ULL;
    get_board(Team::White, Piece::Bishop).bits = 0x2400000000000000ULL;
    get_board(Team::Black, Piece::Bishop).bits = 0x0000000000000024ULL;
    get_board(Team::White, Piece::Queen).bits  = 0x1000000000000000ULL;
    get_board(Team::Black, Piece::Queen).bits  = 0x0000000000000010ULL;
    get_board(Team::White, Piece::King).bits   = 0x0800000000000000ULL;
    get_board(Team::Black, Piece::King).bits   = 0x0000000000000008ULL;

    white_board.bits = black_board.bits = 0;
    for (int i = 0; i < 6; i++)
    {
        white_board.bits |= get_board(Team::White, (Piece) i).bits;
        black_board.bits |= get_board(Team::Black, (Piece) i).bits;
    }
}