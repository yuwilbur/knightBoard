#include "Board.h"
#include <iostream>

Board::Board(const unsigned int width, const unsigned int height) :
  width_(width),
  height_(height),
  cells_(std::vector<std::vector<Cell>>(width_, std::vector<Cell>(height_, Cell::Free)))
{}

Cell& Board::At(const Coord& coord) {
  if (!IsValid(coord))
    throw std::out_of_range("X or Y is out of range");
  return cells_[coord.x][coord.y];
}

bool Board::IsValid(const Coord& coord) const {
  return (coord.x < (int)width_ && coord.y < (int)height_);
}

void Board::print() const {
  auto getLabel = [](const Cell& cell) -> char {
    switch (cell) {
    case Cell::Free: return '.';
    case Cell::Water: return 'W';
    case Cell::Rock: return 'R';
    case Cell::Barrier: return 'B';
    case Cell::Teleport: return 'T';
    case Cell::Lava: return 'L';
    default: throw std::invalid_argument("Cell type is not supported. Label will not be found");
    }
  };

  for (size_t y = 0; y < height_; ++y) {
    for (size_t x = 0; x < width_; ++x) {
      std::cout << getLabel(cells_[x][y]) << " ";
    }
    std::cout << std::endl;
  }
}