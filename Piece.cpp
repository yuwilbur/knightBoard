#include "Piece.h"
#include "Coord.h"
#include "GridUtility.h"
#include <queue>
#include <iostream>

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
  Grid<std::pair<Coord, int>> paths(board_.width, board_.height);
  const std::pair<Coord, int> defaultPath = std::make_pair(Coord(), -1);
  paths.Fill(defaultPath);

  std::queue<Coord> moveQueue;
  //auto checkMove = [&](const Coord& source) -> bool {
  //  std::vector<Coord> destinations = GetMoveSet(source);
  //  const int sourceDistance = distances[source];
  //  for (auto& dest : destinations) {
  //    const int destDistance = distances[dest];
  //    const int newDistance = sourceDistance + GetDistance(source, dest);
  //    if (destDistance != -1 && destDistance <= newDistance)
  //      continue;
  //    prevCoord[dest] = source;
  //    distances[dest] = newDistance;
  //    if (board_[dest] == Cell::Teleport) {
  //      const Coord teleportDest = board_.GetTeleportEndpoint(dest);
  //      const int endpointDistance = distances[teleportDest];
  //      if (endpointDistance != -1 && endpointDistance <= newDistance)
  //        continue;
  //      prevCoord[teleportDest] = dest;
  //      distances[teleportDest] = distances[dest];
  //      moveQueue.push(teleportDest);
  //    }
  //    if (dest == end) {
  //      //return true;
  //    }
  //    moveQueue.push(dest);
  //  }
  //  return false;
  //};

  moveQueue.push(start);
  paths[start].first = start;
  paths[start].second = 0;

  while (moveQueue.size() > 0) {
    const Coord move = moveQueue.front();
    const std::vector<Coord> new_moves = ProcessMove(move, paths);
    for (auto& new_move : new_moves) {
      moveQueue.push(new_move);
    }
    moveQueue.pop();
  }

  // Unable to reach end

  GridUtility::print(paths);

  if (paths[end].first == Coord())
    return{};
  std::vector<Coord> result;
  for (Coord coord = end; coord != start; coord = paths[coord].first) {
    result.push_back(coord);
  }
  result.push_back(start);
  return result;
}

//std::vector<Coord> Piece::ComputeLongestPath(const Coord& start, const Coord& end) const {
//  Grid<Coord> prevCoord(board_.width, board_.height);
//  prevCoord.Fill(Coord(-1, -1));
//  Grid<int> distances(board_.width, board_.height);
//  distances.Fill(-1);
//
//  std::queue<Coord> moveQueue;
//  auto checkMove = [&](const Coord& source) -> bool {
//    std::vector<Coord> destinations = GetMoveSet(source);
//    const int sourceDistance = distances[source];
//    for (auto& dest : destinations) {
//      const int destDistance = distances[dest];
//      const int newDistance = sourceDistance + GetDistance(source, dest);
//      if (destDistance != -1 && destDistance <= newDistance)
//        continue;
//      prevCoord[dest] = source;
//      distances[dest] = newDistance;
//      if (board_[dest] == Cell::Teleport) {
//        const Coord teleportDest = board_.GetTeleportEndpoint(dest);
//        const int endpointDistance = distances[teleportDest];
//        if (endpointDistance != -1 && endpointDistance <= newDistance)
//          continue;
//        prevCoord[teleportDest] = dest;
//        distances[teleportDest] = distances[dest];
//        moveQueue.push(teleportDest);
//      }
//      moveQueue.push(dest);
//    }
//    return false;
//  };
//
//  moveQueue.push(start);
//  distances[start] = 0;
//  prevCoord[start] = start;
//
//  while (moveQueue.size() > 0) {
//    if (checkMove(moveQueue.front()))
//      break;
//    moveQueue.pop();
//  }
//
//  // Unable to reach end
//  if (distances[end] == 0)
//    return{};
//
//  GridUtility::print(distances);
//
//  std::vector<Coord> path;
//  for (Coord coord = end; coord != start; coord = prevCoord[coord]) {
//    path.push_back(coord);
//  }
//  path.push_back(start);
//  return path;
//}

std::vector<Coord> Piece::ProcessMove(const Coord& move, Grid<std::pair<Coord, int>>& paths) const {
  std::vector<Coord> modifiedMoves = {};
  std::vector<Coord> next_moves = GetMoveSet(move);
  for (auto& next_move : next_moves) {
    const int cached_distance = paths[next_move].second;
    const int distance = paths[move].second + GetDistance(move, next_move);
    if (cached_distance != -1 && distance >= cached_distance)
      continue;
    
    const std::pair<Coord, int> path = std::make_pair(next_move, distance);
    paths[next_move] = path;
    if (board_[next_move] == Cell::Teleport) {
      const Coord endpoint = board_.GetTeleportEndpoint(next_move);
      paths[endpoint] = path;
      modifiedMoves.push_back(endpoint);
    }
    else {
      modifiedMoves.push_back(next_move);
    }
  }
  return modifiedMoves;
  //const int start_distance = distances[start];
  //const int cached_distance = distances[end];
  //const int distance = start_distance + GetDistance(start, end);
  //if (cached_distance != -1 && distance >= cached_distance)
  //  return{};
  //
  //paths[end] = start;
  //distances[end] = distance;
  //if (board_[end] == Cell::Teleport) {
  //  const Coord endpoint = board_.GetTeleportEndpoint(end);
  //  paths[endpoint] = start;
  //  distances[endpoint] = distance;
  //}
}
