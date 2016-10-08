#pragma once
#include "Grid.h"
#include "Cell.h"

#include <utility>

class Board :
  public Grid<Cell>
{
public:
  Board(const unsigned int width, const unsigned int height) : Grid<Cell>(width, height) {};

  void ConstructTeleportEndpoints();
  Coord GetTeleportEndpoint(const Coord& start) const;

protected:
  std::pair<Coord, Coord> teleport_;
};
