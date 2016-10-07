#include "Board.h"
#include "Knight.h"
#include <iostream>

int main() {
  std::cout << "START" << std::endl;

  Board board(7, 7);
  board.print();

  std::cout << std::endl;
  
  Knight knight;
  Cell start = board.Get(5, 5);
  for (size_t y = 0; y < 7; ++y) {
    for (size_t x = 0; x < 7; ++x) {
      Cell end = board.Get(x, y);
      std::cout << (knight.IsMoveValid(start, end) ? '1' : '.') << " ";
    }
    std::cout << std::endl;
  }
  
  std::cout << "END" << std::endl;
  system("pause");
  return 0;
}