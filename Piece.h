#pragma once
#include "Board.h"
#include "Cell.h"
#include "Node.h"
#include <vector>
#include <utility>
#include <functional>

class Piece {
  friend class Game;   
public:
  Piece() = default;
  virtual ~Piece() = default;

  std::vector<Coord> ComputeShortestPath(const Coord& start, const Coord& end) const;
  std::vector<Coord> ComputeLongestPath(const Coord& start, const Coord& end);

protected:
  Coord position;

  virtual bool IsMoveValid(const Coord& start, const Coord& end, const Board& board) const = 0;
  virtual int GetDistance(const Coord& start, const Coord& end, const Board& board) const = 0;
  virtual std::vector<Coord> GetMoveSet(const Coord& start, const Board& board) const = 0;

  std::vector<Coord> ProcessMoveBFS(const Coord& start, Grid<NodeBFS>& paths) const;
  void ProcessMoveDFS(const Coord& src, const Coord& end, Grid<NodeDFS>& paths, int parent_distance);
  std::vector<Coord> longest_path_;
  int longest_path_distance_;
};
