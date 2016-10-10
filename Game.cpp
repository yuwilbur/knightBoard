#include "Game.h"
#include "GridUtility.h"

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

void Game::PrintBoard() const {
  GridUtility::Print(board_, {std::make_pair(knight_->position, Cell::Knight)});
}