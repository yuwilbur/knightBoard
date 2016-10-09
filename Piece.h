#pragma once
#include "Board.h"
#include "Cell.h"
#include "Node.h"
#include <vector>
#include <utility>
#include <functional>

class Piece {
public:
  Piece(const Board& board) : board_(board) {};
  virtual ~Piece() = default;

  bool IsSequenceValid(const std::vector<Coord>& path) const;
  std::vector<Coord> ComputeShortestPath(const Coord& start, const Coord& end) const;
  std::vector<Coord> ComputeLongestPath(const Coord& start, const Coord& end) const;

  virtual bool IsMoveValid(const Coord& start, const Coord& end) const = 0;
  virtual int GetDistance(const Coord& start, const Coord& end) const = 0;
  virtual std::vector<Coord> GetMoveSet(const Coord& start) const = 0;

protected:
  const Board& board_;

  std::vector<Coord> ProcessMoveBFS(const Coord& start, Grid<NodeBFS>& paths) const;
};
