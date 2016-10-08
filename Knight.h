#pragma once
#include "Piece.h"

class Knight :
  public Piece
{
public:
  Knight(const Board<Cell>& board) : Piece(board) {};

  int GetDistance(const Coord& start, const Coord& end) const override;
  bool IsMoveValid(const Coord& start, const Coord& end) const override;
  std::vector<Coord> GetMoveSet(const Coord& start) const override;
};
