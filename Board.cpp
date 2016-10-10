#include "Board.h"
#include <iostream>

void Board::Setup() {
  ConstructStartEndPoints();
  ConstructTeleportEndpoints();
}

Board Board::SubBoard(const Coord& top_left, const unsigned int new_width, const unsigned int new_height) const {
  if ((top_left.x + new_width) > width || (top_left.y + new_height) > height)
    throw std::invalid_argument("New width or height are too large");
  Board board(new_width, new_height);
  for (unsigned int x = 0; x < new_width; ++x) {
    for (unsigned int y = 0;  y < new_height; ++y) {
      const Coord coord(x, y);
      board[coord] = (*this)[coord + top_left];
    }
  }
  board.Setup();
  return board;
}

void Board::ConstructStartEndPoints() {
  for (size_t x = 0; x < width; ++x) {
    for (size_t y = 0; y < height; ++y) {
      const Coord coord = Coord(x, y);
      const Cell cell = (*this)[coord];
      if (cell == Cell::Start)
        start_ = coord;
      if (cell == Cell::End)
        end_ = coord;
      if (!start_.IsNull() && !end_.IsNull())
        return;
    }
  }
}

void Board::ConstructTeleportEndpoints() {
  if (!teleport_.first.IsNull() && !teleport_.second.IsNull())
    throw std::runtime_error("Currently unable to support more than 1 teleport");
  for (size_t x = 0; x < width; ++x) {
    for (size_t y = 0; y < height; ++y) {
      const Coord coord = Coord(x, y);
      if ((*this)[coord] != Cell::Teleport)
        continue;
      if (teleport_.first.IsNull())
        teleport_.first = coord;
      else if (teleport_.second.IsNull())
        teleport_.second = coord;
      else
        throw std::runtime_error("More than 2 Teleports detected. Cannot support multiple teleports");
    }
  }
  if (!teleport_.first.IsNull() && teleport_.second.IsNull())
    throw std::runtime_error("Only 1 Teleport is detected. Teleport endpoint is not complete");
}

Coord Board::GetTeleportEndpoint(const Coord& endpoint) const {
  if (teleport_.first == endpoint)
    return teleport_.second;
  if (teleport_.second == endpoint)
    return teleport_.first;
  throw std::invalid_argument("Coord is not an endpoint of the teleport");
}