#pragma once
#include <stdint.h>

struct Cell {
  enum class State : uint8_t {
    Invalid = 0,
    Start = 1,
    End = 2,

    Free = 10,
    Water = 11,
    Rock = 12,
    Barrier = 13,
    Teleport = 14,
    Lava = 15,

    Knight = 20,
  };

  Cell(const int x, const int y, const State state) :
    x(x), y(y), state(state)
  {}
  const int x = 0;
  const int y = 0;
  State state = State::Invalid;
};