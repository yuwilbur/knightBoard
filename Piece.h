#pragma once
#include "Board.h"
#include "Cell.h"
#include "Node.h"
#include <vector>

class Piece {
  friend class Game;   
public:
  Piece() = default;
  virtual ~Piece() = default;

protected:
  Coord position;

  virtual bool IsMoveValid(const Coord& start, const Coord& end, const Board& board) const = 0;
  virtual int GetDistance(const Coord& start, const Coord& end, const Board& board) const = 0;
  virtual std::vector<Coord> GetMoveSet(const Coord& start, const Board& board) const = 0;
};
