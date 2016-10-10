#pragma once
#include "Piece.h"

class Knight :
  public Piece
{
public:
  Knight() = default;

protected:
  bool IsMoveValid(const Coord& start, const Coord& end, const Board& board) const override;
  int GetDistance(const Coord& start, const Coord& end, const Board& board) const override;
  std::vector<Coord> GetMoveSet(const Coord& start, const Board& board) const override;
};
