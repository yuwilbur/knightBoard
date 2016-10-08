#include "Piece.h"
#include "Coord.h"
#include "GridUtility.h"
#include <queue>

bool Piece::IsSequenceValid(const std::vector<Coord>& path) const {
  if (path.size() < 2)
    throw std::invalid_argument("Path is too short. Cannot compute sequence");
  for (size_t i = 0; i < path.size(); ++i) {
    if (!IsMoveValid(path[i], path[i - 1]))
      return false;
  }
  return true;
}

std::vector<Coord> Piece::ComputeShortestPath(const Coord& start, const Coord& end) const {
  Grid<Coord> prevCoord(board_.width, board_.height);
  prevCoord.Fill(Coord(-1, -1));
  Grid<int> distances(board_.width, board_.height);
  distances.Fill(-1);

  std::queue<Coord> moveQueue;
  auto checkMove = [&](const Coord& source) -> bool {
    std::vector<Coord> destinations = GetMoveSet(source);
    const int sourceDistance = distances[source];
    for (auto& dest : destinations) {
      const int destDistance = distances[dest];
      const int newDistance = sourceDistance + GetDistance(source, dest);
      if (destDistance != -1 && destDistance <= newDistance)
        continue;
      prevCoord[dest] = source;
      distances[dest] = newDistance;
      if (board_[dest] == Cell::Teleport) {
        const Coord teleportDest = board_.GetTeleportEndpoint(dest);
        const int endpointDistance = distances[teleportDest];
        if (endpointDistance != -1 && endpointDistance <= newDistance)
          continue;
        prevCoord[teleportDest] = dest;
        distances[teleportDest] = distances[dest];
        moveQueue.push(teleportDest);
      }
      if (dest == end) {
        //return true;
      }
      moveQueue.push(dest);
    }
    return false;
  };

  moveQueue.push(start);
  distances[start] = 0;
  prevCoord[start] = start;

  while (moveQueue.size() > 0) {
    if (checkMove(moveQueue.front()))
      break;
    moveQueue.pop();
  }

  // Unable to reach end
  if (distances[end] == 0)
    return{};

  GridUtility::print(distances);

  std::vector<Coord> path;
  for (Coord coord = end; coord != start; coord = prevCoord[coord]) {
    path.push_back(coord);
  }
  path.push_back(start);
  return path;
}
