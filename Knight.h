#pragma once
#include "Piece.h"

class Knight :
  public Piece
{
public:
  Knight(const Board& board) : Piece(board) {};

  bool IsMoveValid(const Coord& start, const Coord& end) const override;
  int GetDistance(const Coord& start, const Coord& end) const override;
  std::vector<Coord> GetMoveSet(const Coord& start) const override;
};
