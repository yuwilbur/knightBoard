#pragma once
#include "Grid.h"
#include "Cell.h"

class Board :
  public Grid<Cell>
{
public:
  Board(const unsigned int width, const unsigned int height) : Grid<Cell>(width, height) {};
};
