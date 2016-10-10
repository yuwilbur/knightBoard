#pragma once
#include "Board.h"
#include "Knight.h"
#include <memory>
#include <unordered_map>

class Game {
public:
  Game(Board board);

  void PrintBoard() const;

  std::shared_ptr<Knight> GetKnight() { return knight_; };
  
  void Move(const std::shared_ptr<Piece>& piece, const std::vector<Coord>& path, const bool print_per_move = false) const;
  
  std::vector<Coord> ShortestPathToEnd(const std::shared_ptr<Piece>& piece) const;
  std::vector<Coord> ShortestPath(const std::shared_ptr<Piece>& piece, const Coord& target) const;

protected:
  Board board_;
  std::shared_ptr<Knight> knight_;

  std::vector<Coord> GetMoveSet(const std::shared_ptr<Piece>& piece, const Coord& start) const;
  int GetDistance(const std::shared_ptr<Piece>& piece, const Coord& start, const Coord& end) const;
};