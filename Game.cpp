#include "Game.h"
#include "Node.h"
#include "GridUtility.h"
#include <queue>
#include <functional>

Game::Game(Board board) :
  board_(board),
  knight_(std::make_shared<Knight>())
{
  knight_->position = board_.GetStart();
}

void Game::Move(const std::shared_ptr<Piece>& piece, const std::vector<Coord>& path, const bool print_per_move) const {
  for (size_t i = 0; i < path.size(); ++i) {
    if (!piece->IsMoveValid(piece->position, path[i], board_))
      throw std::runtime_error("Piece move is valid");
    piece->position = path[i];
    if (print_per_move)
      PrintBoard();
  }
}

std::vector<Coord> Game::ShortestPathToEnd(const std::shared_ptr<Piece>& piece) const {
  return ShortestPath(piece, board_.GetEnd());
}

std::vector<Coord> Game::ShortestPath(const std::shared_ptr<Piece>& piece, const Coord& target) const {
  // Apply Dijkstra's algorithm (Breadth-first-search)
  Grid<NodeBFS> paths(board_.width, board_.height);
  paths.Fill({ Coord(), -1 });

  std::queue<Coord> moveQueue;
  const Coord start = piece->position;
  moveQueue.push(start);
  paths[start].distance = 0;

  while (moveQueue.size() > 0) {
    const Coord src = moveQueue.front();
    std::vector<Coord> next_moves = {};
    std::vector<Coord> possible_moves = GetMoveSet(piece, src);
    for (auto& dst : possible_moves) {
      const int old_distance = paths[dst].distance;
      const int new_distance = paths[src].distance + GetDistance(piece, src, dst);
      if (old_distance != -1 && old_distance <= new_distance)
        continue;
      const NodeBFS node = { src, new_distance };
      paths[dst] = node;
      if (board_[dst] == Cell::Teleport) {
        const Coord endpoint = board_.GetTeleportEndpoint(dst);
        paths[endpoint] = node;
        next_moves.push_back(endpoint);
      }
      else {
        next_moves.push_back(dst);
      }
    }
    for (auto& next_move : next_moves) {
      moveQueue.push(next_move);
    }
    moveQueue.pop();
  }

  // Unable to reach the end
  if (paths[target].parent.IsNull())
    return{};
  std::vector<Coord> result = {};
  for (Coord coord = target; coord != start; coord = paths[coord].parent) {
    result.push_back(coord);
  } 
  std::reverse(result.begin(), result.end());
  return result;
}


std::vector<Coord> Game::GetMoveSet(const std::shared_ptr<Piece>& piece, const Coord& start) const {
  return piece->GetMoveSet(start, board_);
}

int Game::GetDistance(const std::shared_ptr<Piece>& piece, const Coord& start, const Coord& end) const {
  return piece->GetDistance(start, end, board_);
}

void Game::PrintBoard() const {
  GridUtility::Print(board_, { std::make_pair(knight_->position, Cell::Knight) });
}

/*
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
}*/