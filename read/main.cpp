// ifstream constructor.
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <bitset>

#define line std::cout<<std::endl;

std::bitset<8> binary(char );
int main () {

  //constructors of input and output stream
  /*
   *We create an file stream named ifs based on the input file with mode in
   *We create an file stream named ofs based on the output file with mode out
  */
  std::fstream ifs ("C:/Users/admin/Desktop/practica_3/read/data2.txt", std::ifstream::in);
  std::fstream ofs ("C:/Users/admin/Desktop/practica_3/read/bin.txt", std::ifstream::out);

  char c;
  c = ifs.get();
  //same as ifs.get(c)
  std::cout <<"size of single character in bytes> "<<sizeof(c);
  line            
  std::cout <<"Read file succesfull: "<<ifs.good();
  line

  while (ifs.good()) { //while there are no error on the stream (including eof)
    //we read byte by byte : 8bits
    //we create bitset x of size 8 bits and its value is based on c
    std::bitset<8> x(c);
    //we write the value on the ouput stream
    ofs << binary(c)<<" ";
    //line
    //std::cout <<sizeof(c);
    //we grab next character
    c = ifs.get();
  }

  ifs.close();
  ofs.close();
  return 0;
}

//g++ read.cpp -o read.o 
//./read.o

std::bitset<8> binary(char c)
{
    std::bitset<8> x(c);
    return x;
}
