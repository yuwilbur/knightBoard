#include "PathFinder.h"
#include <queue>

namespace PathFinder {
  bool IsSequenceValid(const std::vector<Coord>& path, const Piece& piece) {
    if (path.size() < 2)
      throw std::invalid_argument("Path is too short. Cannot compute sequence");

    for (size_t i = 1; i < path.size(); ++i) {
      const Coord start = path[i - 1];
      const Coord end = path[i];
      if (!piece.IsMoveValid(start, end))
        return false;
    }
    return true;
  }

  std::vector<Coord> ComputePath(Board board, const Piece& piece, const Coord& start, const Coord& end) {
    //board.At(start.x, start.y, 0);
    //std::queue<Cell> moveQueue;

    //auto addQueue = [&](const Cell& current) {
    //  std::vector<Cell> moves = piece.GetMoveSet(current);
    //  for (auto& move : moves) {
    //    board.SetDistance(move.x, move.y, move.distance + 1);
    //    moveQueue.push(move);
    //  }
    //};

    //while (moveQueue.size() > 0) {

    //}
    //return moves;
    return{};
  }
}