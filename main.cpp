#include <cstdlib>
#include "binops.cpp"
#include <iostream>
#include "board.hpp"

void callback(BitBoard move, Board new_board)
{
    move.print();
    std::cout << std::endl;
    return;
}

int main()
{
    auto b = Board();

    int white, black;

    b.score(&white, &black);

    b.generate_moves(Team::White, callback);

    std::cout << "White Score: " << white << std::endl;
    std::cout << "Black Score: " << black << std::endl;

    std::cout << "Hello world, BetaZero v0.1" << std::endl;
    return EXIT_SUCCESS;
}
