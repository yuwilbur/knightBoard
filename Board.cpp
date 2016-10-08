#include "Board.h"

void Board::SetTeleportEndpoints(const Coord& ep1, const Coord& ep2) {
  if (teleport_.first.IsValid() && teleport_.second.IsValid())
    throw std::runtime_error("Currently unable to support more than 1 teleport");
  teleport_.first = Coord(ep1);
  teleport_.second = Coord(ep2);
  cells_[ep1.x][ep1.y] = Cell::Teleport;
  cells_[ep2.x][ep2.y] = Cell::Teleport;
}

Coord Board::GetTeleportEndpoint(const Coord& start) const {
  if (teleport_.first == start)
    return teleport_.second;
  if (teleport_.second == start)
    return teleport_.first;
  throw std::invalid_argument("Coord is not an endpoint of the teleport");
}