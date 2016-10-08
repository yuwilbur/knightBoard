#pragma once
#include <stdint.h>
#include <limits.h>

enum class Cell : uint8_t {
  // Basic States
  Free = 0,
  Start = 1,
  End = 2,

  // Obstacles
  Water = 10,
  Rock = 11,
  Barrier = 12,
  Teleport = 13,
  Lava = 14,

  // Pieces
  Knight = 20
};

namespace CellAbbreviations {
  constexpr Cell o = Cell::Free;
  constexpr Cell S = Cell::Start;
  constexpr Cell E = Cell::End;

  constexpr Cell W = Cell::Water;
  constexpr Cell R = Cell::Rock;
  constexpr Cell B = Cell::Barrier;
  constexpr Cell T = Cell::Teleport;
  constexpr Cell L = Cell::Lava;

  constexpr Cell K = Cell::Knight;
}
