#pragma once
#include <stdint.h>
#include <limits.h>

enum class Cell : uint8_t {
  Invalid = 0,
  Free = 1,
  Water = 2,
  Rock = 3,
  Barrier = 4,
  Teleport = 5,
  Lava = 6
};
