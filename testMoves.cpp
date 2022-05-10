#include "binops.cpp"
#include "board.hpp"
#include <iostream>

int main(){
    struct BitBoard b = BitBoard();
    
	for(int i = 0;i<64;i++){
        b.bits = 1ull<<i;
    	b.print();
		std::cout<<std::endl;
		b.bits = binops::rookMove(i,0,0);
    	b.print();
		std::cout<<std::endl;

	}

    b.bits = binops::knightMove(36);
    b.print();
	
	std::cout<<std::endl;

    b.bits = 1ll<<36;
    b.print();

    return 0;
}
