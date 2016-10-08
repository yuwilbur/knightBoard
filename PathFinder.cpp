#include "PathFinder.h"
#include "BoardUtility.h"
#include <queue>
#include <iostream>
#include <limits>

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
    Board<Coord> prevCoord(board.width, board.height);
    prevCoord.Fill(Coord(-1, -1));
    Board<int> distances(board.width, board.height);
    distances.Fill(0);

    std::queue<Coord> moveQueue;
    auto checkMove = [&](const Coord& source) -> bool {
      std::vector<Coord> destinations = piece.GetMoveSet(source);
      const int sourceDistance = distances[source];
      for (auto& dest : destinations) {
        const int destDistance = distances[dest];
        const int newDistance = sourceDistance + piece.GetDistance(source, dest);
        if (destDistance != 0 && destDistance <= newDistance)
          continue;
        prevCoord[dest] = source;
        distances[dest] = newDistance;
        BoardUtility::print(distances);
        if (dest == end) {
          return true;
        }
        moveQueue.push(dest);
      }
      return false;
    };

    BoardUtility::print(distances);
    moveQueue.push(start);
    distances[start] = 1;
    prevCoord[start] = start;

    BoardUtility::print(distances);
    while (moveQueue.size() > 0) {
      if (checkMove(moveQueue.front()))
        break;
      moveQueue.pop();
    }

    // Unable to reach end
    if (distances[end] == 0)
      return{};

    BoardUtility::print(prevCoord);

    std::vector<Coord> path;
    for (Coord coord = end; coord != start; coord = prevCoord[coord]) {
      path.push_back(coord);
    }
    path.push_back(start);
    return path;
  }
}