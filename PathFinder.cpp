#include "PathFinder.h"
#include <queue>
#include <unordered_map>

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

  std::vector<Coord> ComputePath(const Board<Cell>& board, const Piece& piece, const Coord& start, const Coord& end) {
    //struct hash_Coord {
    //  size_t operator()(const Coord& coord) const {
    //    return std::hash<int>()(coord.x) ^ std::hash<int>()(coord.y);
    //  }
    //};
    //std::unordered_map<Coord, size_t, hash_Coord> distances;
    //distances.reserve(board.width * board.height);
    //std::queue<Coord> moveQueue;

    //auto addQueue = [&](const Coord& current) {
    //  std::vector<Coord> moves = piece.GetMoveSet(current);
    //  for (auto& move : moves) {
    //    moveQueue.push(move);
    //  }
    //};

    //while (moveQueue.size() > 0) {

    //}
    return{};
  }
}