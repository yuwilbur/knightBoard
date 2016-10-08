#pragma once

struct Coord {
  Coord(const int x = 0, const int y = 0) :
    x(x), y(y) 
  {}
  int x;
  int y;

  bool operator==(const Coord& coord) {
    return (x == coord.x && y == coord.y);
  }

  bool operator!=(const Coord& coord) {
    return !(*this == coord);
  }

  Coord operator-(const Coord& coord) const {
    return Coord(x - coord.x, y - coord.y);
  }

  Coord operator+(const Coord& coord) const {
    return Coord(x + coord.x, y + coord.y);
  }
};
