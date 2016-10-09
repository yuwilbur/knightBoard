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
  Grid<Node> paths(board_.width, board_.height);
  const Node defaultNode = { Coord(), -1 };
  paths.Fill(defaultNode);

  std::queue<Coord> moveQueue;
  moveQueue.push(start);
  paths[start].distance = 0;

  while (moveQueue.size() > 0) {
    const Coord move = moveQueue.front();
    const std::vector<Coord> new_moves = ProcessMove(move, paths);
    for (auto& new_move : new_moves) {
      moveQueue.push(new_move);
    }
    moveQueue.pop();
  }

  GridUtility::print(paths);

  // Unable to reach the end
  if (paths[end].parent == Coord())
    return{};
  std::vector<Coord> result = {};
  for (Coord coord = end; coord != start; coord = paths[coord].parent) {
    result.push_back(coord);
  }
  result.push_back(start);
  return result;
}

std::vector<Coord> Piece::ComputeLongestPath(const Coord& start, const Coord& end) const {
  Grid<Node> paths(board_.width, board_.height);
  const Node defaultNode = { Coord(), -1 };
  paths.Fill(defaultNode);

  std::queue<Coord> moveQueue;
  moveQueue.push(start);
  paths[start].distance = 0;

  int i = 0;
  while (moveQueue.size() > 0) {
    const Coord move = moveQueue.front();
    if (i++ % 10000 == 0)
      GridUtility::print(paths);
    const std::vector<Coord> new_moves = ProcessMove(move, paths, std::less_equal<int>());
    for (auto& new_move : new_moves) {
      moveQueue.push(new_move);
    }
    moveQueue.pop();
  }

  GridUtility::print(paths);

  // Unable to reach the end
  if (paths[end].parent == Coord())
    return{};
  std::vector<Coord> result = {};
  for (Coord coord = end; coord != start; coord = paths[coord].parent) {
    result.push_back(coord);
  }
  result.push_back(start);
  return result;
}

std::vector<Coord> Piece::ProcessMove(const Coord& curr_move, Grid<Node>& paths, const std::function<bool(int, int)>& pred) const {
  std::vector<Coord> processed_moves = {};
  std::vector<Coord> next_moves = GetMoveSet(curr_move);

  auto isWithinPath = [&](Coord coord, const Coord& target) -> bool {
    while (coord != Coord()) {
      if (coord == target) {
        return true;
      }
      coord = paths[coord].parent;
    }
    return false;
  };
  
  for (auto& next_move : next_moves) {
    const int cached_distance = paths[next_move].distance;
    const int distance = paths[curr_move].distance + GetDistance(curr_move, next_move);
    if (cached_distance != -1 && pred(distance, cached_distance))
      continue;
    if (isWithinPath(curr_move, next_move))
      continue;

    const Node node = { curr_move, distance };
    paths[next_move] = node;
    if (board_[next_move] == Cell::Teleport) {
      const Coord endpoint = board_.GetTeleportEndpoint(next_move);
      paths[endpoint] = node;
      processed_moves.push_back(endpoint);
    }
    else {
      processed_moves.push_back(next_move);
    }
  }
  return processed_moves;
}
