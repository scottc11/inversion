/**
 * https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
 * 
 * The & (bitwise AND) in C or C++ takes two numbers as operands and does AND on every bit of two numbers. The result of AND is 1 only if both bits are 1.
 * The | (bitwise OR) in C or C++ takes two numbers as operands and does OR on every bit of two numbers. The result of OR is 1 if any of the two bits is 1.
 * The ^ (bitwise XOR) in C or C++ takes two numbers as operands and does XOR on every bit of two numbers. The result of XOR is 1 if the two bits are different.
 * The << (left shift) in C or C++ takes two numbers, left shifts the bits of the first operand, the second operand decides the number of places to shift.
 * The >> (right shift) in C or C++ takes two numbers, right shifts the bits of the first operand, the second operand decides the number of places to shift.
 * The ~ (bitwise NOT) in C or C++ takes one number and inverts all bits of it 
 * 
 * 
 * https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
**/


#include <iostream>
#include <bitset>

// using namespace std;



// compile -->  g++ -o bitwise bitwise.cpp
// run     -->  ./bitwise

int main()
{
  unsigned char a = 0b00000011;
  unsigned char b = 0b00000011;

  std::bitset<8> output(1 << 4);

  std::cout << output << std::endl;
  return 0;
}