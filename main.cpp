#include "Board.h"
#include <iostream>

int main() {
  std::cout << "START" << std::endl;

  Board board(10, 10);
  board.print();

  std::cout << "END" << std::endl;
  system("pause");
  return 0;
}