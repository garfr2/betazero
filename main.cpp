#include <cstdlib>

#include <iostream>

#include "board.hpp"

int main()
{
    auto b = Board();

    b.black_board.print();


    std::cout << "Hello world, BetaZero v0.1" << std::endl;
    return EXIT_SUCCESS;
}