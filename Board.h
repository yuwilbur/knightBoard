#pragma once
#include <vector>

class Board {
public:
  enum class Cell : char {
    Free = 0, // Free
    Water = 1, // Water
    Rock = 2, // Rock
    Barrier = 3, // Barrier
    Teleport = 4, // Teleport
    Lava = 5  // Lava
  };

  Board(const unsigned int width, const unsigned int height);

  std::vector<Cell>& operator[](const size_t x) { return cells_[x]; }
  
  void print();

private:
  const unsigned int width_;
  const unsigned int height_;
  std::vector<std::vector<Cell>> cells_;
};