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
  // Apply Dijkstra's algorithm (Breadth-first-search)
  Grid<NodeBFS> paths(board_.width, board_.height);
  paths.Fill({Coord(), -1});

  std::queue<Coord> moveQueue;
  moveQueue.push(start);
  paths[start].distance = 0;

  int i = 0;
  while (moveQueue.size() > 0) {
    const Coord move = moveQueue.front();
    if (i++ % 1000 == 0)
      GridUtility::print(paths);
    const std::vector<Coord> next_moves = ProcessMoveBFS(move, paths);
    for (auto& next_move: next_moves) {
      moveQueue.push(next_move);
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
  Grid<NodeBFS> paths(board_.width, board_.height);
  const NodeBFS defaultNode = { Coord(), -1 };
  paths.Fill(defaultNode);

  std::queue<Coord> moveQueue;
  moveQueue.push(start);
  paths[start].distance = 0;

  int i = 0;
  while (moveQueue.size() > 0) {
    const Coord move = moveQueue.front();
    if (i++ % 10000 == 0)
      GridUtility::print(paths);
    const std::vector<Coord> new_moves = ProcessMoveBFS(move, paths);
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

std::vector<Coord> Piece::ProcessMoveBFS(const Coord& start, Grid<NodeBFS>& paths) const {
  std::vector<Coord> next_moves = {};
  std::vector<Coord> possible_moves = GetMoveSet(start);
  for (auto& end : possible_moves) {
    const int old_distance = paths[end].distance;
    const int new_distance = paths[start].distance + GetDistance(start, end);
    if (old_distance != -1 && old_distance <= new_distance)
      continue;
    const NodeBFS node = { start, new_distance };
    paths[end] = node;
    if (board_[end] == Cell::Teleport) {
      const Coord endpoint = board_.GetTeleportEndpoint(end);
      paths[endpoint] = node;
      next_moves.push_back(endpoint);
    }
    else {
      next_moves.push_back(end);
    }
  }
  return next_moves;
}
