#include "Board.h"
#include <iostream>

void Board::ConstructTeleportEndpoints() {
  if (teleport_.first.IsValid() && teleport_.second.IsValid())
    throw std::runtime_error("Currently unable to support more than 1 teleport");
  for (size_t x = 0; x < width; ++x) {
    for (size_t y = 0; y < height; ++y) {
      if (cells_[x][y] != Cell::Teleport)
        continue;
      const Coord coord = Coord(x, y);
      if (!teleport_.first.IsValid())
        teleport_.first = coord;
      else if (!teleport_.second.IsValid())
        teleport_.second = coord;
      else
        throw std::runtime_error("More than 2 Teleports detected. Cannot support multiple teleports");
    }
  }
  if (teleport_.first.IsValid() && !teleport_.second.IsValid())
    throw std::runtime_error("Only 1 Teleport is detected. Teleport endpoint is not complete");
}

Coord Board::GetTeleportEndpoint(const Coord& start) const {
  if (teleport_.first == start)
    return teleport_.second;
  if (teleport_.second == start)
    return teleport_.first;
  throw std::invalid_argument("Coord is not an endpoint of the teleport");
}