#pragma once
#include "Coord.h"
#include <vector>

template <class T>
class Board {
public:
  Board(const unsigned int width, const unsigned int height) :
    width(width),
    height(height),
    cells_(std::vector<std::vector<T>>(width, std::vector<T>(height)))
  {}

  const T& At(const Coord& coord) const {
    if (!IsValid(coord))
      throw std::out_of_range("X or Y is out of range");
    return cells_[coord.x][coord.y];
  }

  T& At(const Coord& coord) {
    if (!IsValid(coord))
      throw std::out_of_range("X or Y is out of range");
    return cells_[coord.x][coord.y];
  }

  bool IsValid(const Coord& coord) const {
    return (coord.x < (int)width && coord.y < (int)height);
  }

  const unsigned int width;
  const unsigned int height;

private:
  std::vector<std::vector<T>> cells_;
};
