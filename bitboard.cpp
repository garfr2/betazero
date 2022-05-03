#include <cstdio>

#include "bitboard.hpp"

BitBoard::BitBoard()
{
    bits = 0;
}

void BitBoard::print()
{
    uint64_t mask = 1;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d ", (mask & bits) != 0);
            mask <<= 1;
        }
        printf("\n");
    }
}