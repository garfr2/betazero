#include <cstdint>
#include <chrono>
#include <iostream>
#include <thread>
//Misc opps for uint64_t
namespace binops{

  //O(n), where n = num of set bits
  inline uint64_t countSetBits(uint64_t x){
    
    uint64_t count;
    for(count=0;x!=0;count++){
      x = x & (x-1);
    }
    
    return count;
  }

  inline uint64_t bitIndex(uint64_t x){//faster than native for 1 bit set. Returns upper limit if otherwise
    
    uint64_t sum = 0;
    uint64_t magicNums[6] = {
    0xaaaaaaaaaaaaaaaa,
    0xcccccccccccccccc,
    0xf0f0f0f0f0f0f0f0,
    0xff00ff00ff00ff00,
    0xffff0000ffff0000,
    0xffffffff00000000,
    };
    
    for(int i = 0;i<6;i++){
      if(x&magicNums[i]){
        sum += 1<<i;
      }
    }
    return sum;
  }

  uint64_t bitIndexSafe(uint64_t x){
		
    uint64_t sum = 0;
    uint64_t magicNums[6] = {
    0xaaaaaaaaaaaaaaaa,
    0xcccccccccccccccc,
    0xf0f0f0f0f0f0f0f0,
    0xff00ff00ff00ff00,
    0xffff0000ffff0000,
    0xffffffff00000000,
    };
		
    for(int i = 5;i>=0;i--){
      if(x&magicNums[i]){
        sum += 1<<i;
        x = x & magicNums[i];
      }
    }
    return sum;
  }

	uint64_t getIndices(uint64_t x){
		int numSetBits = countSetBits(x);
		uint64_t sum;
		
		if(numSetBits == 1){
			sum = bitIndex(x);
		}else{
			int pos = 0;
			while(x != 0){
			
	if(x&1 == 1){
					sum = (sum << 6) | pos;
				}
				x = x>>1;
				pos++;
			}
		}
		return (sum<<6) | numSetBits;
	}

	uint64_t getIndicesNaive(uint64_t x){
		int numSetBits = countSetBits(x);
		uint64_t sum = 0;
			int pos = 0;
			while(x != 0){
				if(x&1 == 1){
					sum = (sum << 6) + pos;
				}
				x = x>>1;
				pos++;
			}
		return sum;
	}



  uint64_t testBitIndex(){
    int avg = 0;
    for(int i = 0;i<64;i++){
      for(int j = 0;j<64;j++){
        uint64_t test = (1ll<<i) | (1ll<<j);
        uint64_t temp = binops::getIndices(test);
				std::cout << i << "," << j << " : " << ((temp>>12) %  64) << " , " << ((temp>>6)%64) << "\t" << (temp%64) << std::endl;
      }
    }
    return avg/(64*64);
  }

  void time(uint64_t (*f)(uint64_t),int iterations,bool clearCache=false){

    //Test func 1
    auto start = std::chrono::high_resolution_clock::now();
    uint64_t avg = 0;
		int reps = 0;
    for(int k = 0;k<iterations;k++){
    for(int i = 0;i<64;i++){
      for(int j = 0;j<64;j++){
        uint64_t test = (1ll<<i);
        avg += f(test);
				if(clearCache){
						std::this_thread::sleep_for(std::chrono::microseconds(1));
						reps++;
				}
      }
    }}
    
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout  << avg << std::endl;
    std::cout << "One set bit: "<< (std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count())<< std::endl;


    //Test func 2
		reps = 0;
    auto start2 = std::chrono::high_resolution_clock::now();
    avg = 0;
    for(int k = 0;k<iterations;k++){
    for(int i = 0;i<64;i++){
      for(int j = 0;j<64;j++){
        uint64_t test = (1ll<<i) | (1ll<<j);
        avg += f(test);
				if(clearCache){
						std::this_thread::sleep_for(std::chrono::microseconds(1));
						reps++;
				}
      }
    }}
		
    auto stop2 = std::chrono::high_resolution_clock::now();
    std::cout << avg << std::endl;
    std::cout << "Two set bit: "<< (std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2).count())<< std::endl;
    
  }


	//Piece moves

	inline uint64_t boundMask(uint64_t col){
		if(col >= 6){
			return 0xfcfcfcfcfcfcfcfc;
		}else if(col <= 2){
			return 0x3f3f3f3f3f3f3f3f;
		}else{
			return 0xffffffffffffffff;
		}

	}	

    uint64_t kingMove(uint64_t index){
		uint64_t k = 0b1110000010100000111;
    int i;
		if(index >= 9){
			return (k<<(index-9)) & boundMask(index-9);
		}else{
			return k>>(9-index) & boundMask(9-index);
		}
	}

  uint64_t knightMove(uint64_t index){
    uint64_t n = 0b10100001000100000000000100010000101;
    if(index >=17){
      return n<<(index-17) & boundMask(index%8);
    }else{
      return n>>(17-index) & boundMask(index%8);
    }
  }

  uint64_t floatingRookMove(uint64_t index){
    uint64_t r = 0;
    for(int i = 0;i<8;i++){//sweep through column
      r = r | (1ull<<((index%8) + i*8));
    }
    r = r ^ (0xffull<<(8*(index/8)));
    return r;
  }

  uint64_t rookMove(uint64_t index, uint64_t allyBoard, uint64_t enemyBoard){
    uint64_t r = 0;
    
    //plus 1
    for(int i = 1;(index+i)%8 >= (index+i-1)%8;i++){
      if((enemyBoard>>(index+i)) & 1 == 1){
        r = r | (1ull<<(index+i));
        break;
      }else if((allyBoard>>(index+i)) & 1 == 1){
        break;
      }else{
        r = r | (1ull<<(index+i));
      }
    }

    //minus 1
    for(int i = 1;(index-i)%8 <= (index-i+1)%8;i++){
      if((enemyBoard>>(index-i)) & 1 == 1){
        r = r | (1ull<<(index-i));
        break;
      }else if((allyBoard>>(index-i)) & 1 == 1){
        break;
      }else{
        r = r | (1ull << (index-i));
      }
    }

    //plus 8
    for(int i = 8;index+i<64;i=i+8){
      if((enemyBoard>>(index+i)) & 1 == 1){
        r = r | (1ull<<(index+i));
        break;
      }else if((allyBoard>>(index+i)) & 1 == 1){
        break;
      }else{
        r = r | (1ull<<(index+i));
      }
    }

    //minus 8
    for(int i = 8;index>=i;i=i+8){
      if((enemyBoard>>(index-i)) & 1 == 1){
        r = r | (1ull<<(index-i));
        break;
      }else if((allyBoard>>(index-i)) & 1 == 1){
        break;
      }else{
        r = r | (1ull << (index-i));
      }
    }

    return r;

  }

  uint64_t naiveBishopMove(uint64_t index){
    uint64_t b = 0;

    for(int i = 1;i<4;i++){
      b = b | (1ull<<(index + 9*i));
      b = b | (1ull<<(index + 7*i));
      b = b | (1ull<<(index - 9*i));
      b = b | (1ull<<(index - 7*i));
    }
    return b;
  }
  


}
