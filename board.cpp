#include <iostream>

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

static int score_bitboard(uint64_t map, int value)
{
    int total = 0;

    while (map != 0)
    {
        if (map & 0x1 != 0)
        {
            total += value;
        }
        map >>= 1;
    }
    return total;
}

void
Board::score(int *_white, int *_black)
{
    int white = 0, black = 0;
    white += score_bitboard(get_board(Team::White, Piece::Pawn).bits, 1);
    black += score_bitboard(get_board(Team::Black, Piece::Pawn).bits, 1);
    white += score_bitboard(get_board(Team::White, Piece::Knight).bits, 3);
    black += score_bitboard(get_board(Team::Black, Piece::Knight).bits, 3);
    white += score_bitboard(get_board(Team::White, Piece::Bishop).bits, 3);
    black += score_bitboard(get_board(Team::Black, Piece::Bishop).bits, 3);
    white += score_bitboard(get_board(Team::White, Piece::Rook).bits, 5);
    black += score_bitboard(get_board(Team::Black, Piece::Rook).bits, 5);
    white += score_bitboard(get_board(Team::White, Piece::Queen).bits, 9);
    black += score_bitboard(get_board(Team::Black, Piece::Queen).bits, 9);
    *_white = white;
    *_black = black;
}

void 
Board::generate_moves(Team team, std::function<void(BitBoard, Board)> callback)
{
    BitBoard bb;
    Board copy = *this;
    uint64_t blockers = team == Team::White ? white_board.bits : black_board.bits;
    uint64_t pawns = get_board(team, Piece::Pawn).bits;

    for (uint64_t index = 1; index != 0; index <<= 1)
    {
        if ((pawns & index) != 0) 
        {
            bb.bits = index >> 8;
            copy.get_board(team, Piece::Pawn).bits = (pawns | bb.bits) ^ index;
            callback(bb, copy);
            copy.get_board(team, Piece::Pawn).bits = pawns;
        }
    }
}