#pragma once
#include "Board.h"
#include "Cell.h"
#include <vector>

class Piece {
public:
  Piece(const Board& board) : board_(board) {};
  virtual ~Piece() = default;

  bool IsSequenceValid(const std::vector<Coord>&) const;
  std::vector<Coord> ComputeShortestPath(const Coord& start, const Coord& end) const;

  virtual int GetDistance(const Coord& start, const Coord& end) const = 0;
  virtual bool IsMoveValid(const Coord& start, const Coord& end) const = 0;
  virtual std::vector<Coord> GetMoveSet(const Coord& start) const = 0;

protected:
  const Board& board_;
};
