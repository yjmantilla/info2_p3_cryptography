// ifstream constructor.
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <bitset>

#define line std::cout<<std::endl; 
int main () {

  std::ifstream ifs ("data.txt", std::ifstream::in);
  int x;
  char c = ifs.get();
  std::cout <<sizeof(c);
  line
  while (ifs.good()) {
    
    std::bitset<8> x(c);
    std::cout << x;
    line
    std::cout <<sizeof(c);
    c = ifs.get();
  }

  ifs.close();

  return 0;
}

//g++ read.cpp -o read.o 
//./read.o


