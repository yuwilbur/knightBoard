#pragma once
#include <stdint.h>
#include <limits.h>

enum class Cell : uint8_t {
  Free = 0,
  Water = 1,
  Rock = 2,
  Barrier = 3,
  Teleport = 4,
  Lava = 5
};
