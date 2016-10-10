#include "Piece.h"
#include "Coord.h"
#include "GridUtility.h"
#include <queue>
#include <iostream>

std::vector<Coord> Piece::ComputeShortestPath(const Coord& start, const Coord& end) const {

  return{};
}

std::vector<Coord> Piece::ComputeLongestPath(const Coord& start, const Coord& end) {
//  Grid<NodeDFS> paths(board_.width, board_.height);
//  paths.Fill({Coord(), false});
//
//  std::queue<Coord> moveQueue;
//  moveQueue.push(start);
//  paths[start].visited = true;
//
//  longest_path_ = {};
//  longest_path_distance_ = 0;
//  ProcessMoveDFS(start, end, paths, 0);
//  return longest_path_;
//}
//
//std::vector<Coord> Piece::ProcessMoveBFS(const Coord& start, Grid<NodeBFS>& paths) const {

  return{};
}

void Piece::ProcessMoveDFS(const Coord& src, const Coord& end, Grid<NodeDFS>& paths, const int parent_distance) {
  //if (src == end) {
  //  if (longest_path_distance_ <= parent_distance)
  //    return;
  //  longest_path_distance_ = parent_distance;
  //  longest_path_ = {};
  //  for (Coord coord = end; coord != Coord(); coord = paths[coord].parent) {
  //    longest_path_.push_back(coord);
  //  }
  //  return;
  //}

  //const std::vector<Coord> possible_moves = GetMoveSet(src, Board(0, 0));
  //for (auto& dest : possible_moves) {
  //  if (paths[dest].visited)
  //    continue;
  //  const int distance = parent_distance + GetDistance(src, dest, Board(0, 0));
  //  const NodeDFS node = { src, true };
  //  GridUtility::print(paths);
  //  paths[dest] = node;
  //  if (board_[dest] == Cell::Teleport) {
  //    const Coord endpoint = board_.GetTeleportEndpoint(dest);
  //    paths[endpoint] = node;
  //    ProcessMoveDFS(endpoint, end, paths, distance);
  //    paths[endpoint].visited = false;
  //  }
  //  else {
  //    ProcessMoveDFS(dest, end, paths, distance);
  //    paths[dest].visited = false;
  //  }
  //}
}
