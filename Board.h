#pragma once
#include "Grid.h"
#include "Cell.h"

#include <utility>

class Board :
  public Grid<Cell>
{
public:
  Board(const unsigned int width, const unsigned int height) : Grid<Cell>(width, height) {};

  void Setup();

  Board SubBoard(const Coord& top_left, const unsigned int new_width, const unsigned int new_height) const;

  Coord GetStart() const { return start_; }
  Coord GetEnd() const { return end_; }
  Coord GetTeleportEndpoint(const Coord& endpoint) const;

protected:
  Coord start_;
  Coord end_;
  std::pair<Coord, Coord> teleport_;

  void ConstructStartEndPoints();
  void ConstructTeleportEndpoints();
};
