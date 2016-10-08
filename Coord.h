#pragma once

struct Coord {
  Coord(const int x = -1, const int y = -1) :
    x(x), y(y) 
  {}
  int x;
  int y;

  bool IsValid() const {
    return (x != -1 && y != -1);
  }

  bool operator==(const Coord& coord) const {
    return (x == coord.x && y == coord.y);
  }

  bool operator!=(const Coord& coord) const {
    return !(*this == coord);
  }

  Coord operator-(const Coord& coord) const {
    return Coord(x - coord.x, y - coord.y);
  }

  Coord operator+(const Coord& coord) const {
    return Coord(x + coord.x, y + coord.y);
  }
};
