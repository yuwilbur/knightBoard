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

  GridUtility::print(paths);

  // Unable to reach the end
  if (paths[end].first == Coord())
    return{};
  std::vector<Coord> result = {};
  for (Coord coord = end; coord != start; coord = paths[coord].first) {
    result.push_back(coord);
  }
  result.push_back(start);
  return result;
}

std::vector<Coord> Piece::ComputeLongestPath(const Coord& start, const Coord& end) const {
  Grid<std::pair<Coord, int>> paths(board_.width, board_.height);
  const std::pair<Coord, int> defaultPath = std::make_pair(Coord(), -1);
  paths.Fill(defaultPath);

  std::queue<Coord> moveQueue;
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

  GridUtility::print(paths);

  // Unable to reach the end
  if (paths[end].first == Coord())
    return{};
  std::vector<Coord> result = {};
  for (Coord coord = end; coord != start; coord = paths[coord].first) {
    result.push_back(coord);
  }
  result.push_back(start);
  return result;
}

std::vector<Coord> Piece::ProcessMove(const Coord& curr_move, Grid<std::pair<Coord, int>>& paths) const {
  std::vector<Coord> processed_moves = {};
  std::vector<Coord> next_moves = GetMoveSet(curr_move);
  auto getTotalDistance = [this](Coord coord, const Grid<std::pair<Coord, int>>& paths) -> int {
    int distance = 0;
    while (paths[coord].first != coord) {
      distance += GetDistance(paths[coord].first, coord);
      coord = paths[coord].first;
    }
    return distance;
  };
  
  for (auto& next_move : next_moves) {
    const int cached_distance = paths[next_move].second;
    const int distance = getTotalDistance(curr_move, paths) + GetDistance(curr_move, next_move);
    if (cached_distance != -1 && distance >= cached_distance)
      continue;
    
    const std::pair<Coord, int> path = std::make_pair(curr_move, distance);
    paths[next_move] = path;
    if (board_[next_move] == Cell::Teleport) {
      const Coord endpoint = board_.GetTeleportEndpoint(next_move);
      paths[endpoint] = path;
      processed_moves.push_back(endpoint);
    }
    else {
      processed_moves.push_back(next_move);
    }
  }
  return processed_moves;
}
