#include <cstdlib>
#include "binops.cpp"
#include <iostream>

int main()
{
    std::cout << "Hello world, BetaZero v0.1" << std::endl;
		//binops::testBitIndex();
    binops::time(&binops::getIndecies,10,true);
		binops::time(&binops::getIndeciesNaive,10,true);
    return EXIT_SUCCESS;
}