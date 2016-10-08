#pragma once
#include <stdint.h>
#include <limits.h>

enum class Cell : uint8_t {
  Free = 0, // Free
  Water = 1, // Water
  Rock = 2, // Rock
  Barrier = 3, // Barrier
  Teleport = 4, // Teleport
  Lava = 5, // Lava

  Knight = 10 // Knight
};

namespace CellAbbreviations {
  constexpr Cell o = Cell::Free;
  constexpr Cell W = Cell::Water;
  constexpr Cell R = Cell::Rock;
  constexpr Cell B = Cell::Barrier;
  constexpr Cell T = Cell::Teleport;
  constexpr Cell L = Cell::Lava;
}
