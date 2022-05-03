#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>

class BitBoard
{
public:
    uint64_t bits;

    BitBoard();

    bool 
    has_piece(int col, int row)
    {
        uint64_t offset = ((uint64_t) (7 - col)) * 8ULL + row;
        return (bits & (1ULL << offset)) != 0;
    }

    void print();
};

#endif /* BOARD_HPP */