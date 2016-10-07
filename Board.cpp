#include "Board.h"
#include <iostream>

Board::Board(const unsigned int width, const unsigned int height) :
  width_(width),
  height_(height)
{
  cells_ = std::vector<std::vector<Cell::State>>(width_, std::vector<Cell::State>(height_, Cell::State::Free));
}

Cell Board::Get(const size_t x, const size_t y) const {
  if (x >= width_) 
    throw std::out_of_range("X is out of range");
  if (y >= height_)
    throw std::out_of_range("Y is out of range");
  return Cell(x, y, cells_[x][y]);
}

void Board::print() const {
  auto getLabel = [](const Cell::State state) -> char {
    switch (state) {
    case Cell::State::Free: return '.';
    case Cell::State::Water: return 'W';
    case Cell::State::Rock: return 'R';
    case Cell::State::Barrier: return 'B';
    case Cell::State::Teleport: return 'T';
    case Cell::State::Lava: return 'L';
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