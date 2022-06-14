#include "human_player.h"

typename Checkers::Board::Move Checkers::HumanPlayer::get_move() const {
  std::cout << std::endl << name() << " move: ";
  std::string src, dest;
  is >> src >> dest;
  return Board::Move(board_.spot(src), board_.spot(dest), board_);
}
