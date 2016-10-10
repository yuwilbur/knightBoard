#include "Game.h"
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
  if (paths[target].parent == Coord())
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
