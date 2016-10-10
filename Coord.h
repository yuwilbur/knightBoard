#pragma once
#include  <iostream>

struct Coord {
  Coord(const int x = -1, const int y = -1) :
    x(x), y(y) 
  {}
  int x;
  int y;

  bool IsNull() const {
    return *this == Coord();
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

  Coord operator/(const int divisor) const {
    return Coord(x / divisor, y / divisor);
  }

  Coord operator*(const int multiplier) const {
    return Coord(x * multiplier, y * multiplier);
  }

  friend std::ostream& operator<<(std::ostream& os, const Coord& coord) {
    os << coord.x << "," << coord.y;
    return os;
  }
};
