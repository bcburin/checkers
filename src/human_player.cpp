#include "human_player.h"

typename Checkers::Board::Move Checkers::HumanPlayer::get_move() const {
  set_color(Checker(piece_color_).color_w32());
  std::cout << std::endl << name() << " move: ";
  set_color(WRITING_COLOR);
  std::string src, dest;
  is >> src >> dest;
  reset_color();
  return Board::Move(board_.spot(src), board_.spot(dest), board_);
}
