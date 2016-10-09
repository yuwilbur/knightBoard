#pragma once
#include "Coord.h"

struct NodeBFS {
  // This is kind of ugly. Because Node will be stored in a grid format instead of a linked-list, 
  // the parent can also be defined as a coordinate on the grid instead of Node *
  Coord parent;
  int distance;
};
