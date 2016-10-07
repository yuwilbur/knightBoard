#pragma once
#include "Piece.h"

class Knight :
  public Piece
{
public:
  Knight() = default;

  bool IsMoveValid(const Cell& start, const Cell& end) override;
};
