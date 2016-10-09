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

std::vector<Coord> Piece::ComputeLongestPath(const Coord& start, const Coord& end) {
  Grid<NodeDFS> paths(board_.width, board_.height);
  paths.Fill({Coord(), false, -1});

  std::queue<Coord> moveQueue;
  moveQueue.push(start);
  paths[start].visited = true;
  paths[start].distance = 0;

  longest_path_ = {};
  longest_path_distance_ = 0;
  ProcessMoveDFS(start, end, paths, 0);
  GridUtility::print(paths);
  std::cout << "END" << std::endl;
  return longest_path_;
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

void Piece::ProcessMoveDFS(const Coord& src, const Coord& end, Grid<NodeDFS>& paths, const int parent_distance) {
  if (src == end) {
    if (longest_path_distance_ <= parent_distance)
      return;
    longest_path_distance_ = parent_distance;
    longest_path_ = {};
    for (Coord coord = end; coord != Coord(); coord = paths[coord].parent) {
      longest_path_.push_back(coord);
    }
    return;
  }

  const std::vector<Coord> possible_moves = GetMoveSet(src);
  for (auto& dest : possible_moves) {
    if (paths[dest].visited)
      continue;
    const int distance = parent_distance + GetDistance(src, dest);
    if (paths[dest].distance < distance) {
      GridUtility::print(paths);
    }
    const int nodeDistance = std::max(paths[dest].distance, distance);
    const NodeDFS node = { src, true, nodeDistance };
    paths[dest] = node;
    ProcessMoveDFS(dest, end, paths, distance);
    paths[dest].visited = false;
    //if (board_[dest] == Cell::Teleport) {
    //  const Coord endpoint = board_.GetTeleportEndpoint(dest);
    //  paths[endpoint] = node;
    //  ProcessMoveDFS(endpoint, end, paths);
    //  paths[endpoint].visited = false;
    //}
    //else {
    //}
  }
}
