#include "player.h"

int Checkers::Player::num_pieces() const {
  int num_pieces_ = 0;
  for(int x = 0; x != S; ++x) {
    for (int y = 0; y != S ; ++y) {
      if (board_.spot(x,y).piece() && board_.spot(x,y).piece()->color() == piece_color_) 
        ++num_pieces_;
    }
  }
  return num_pieces_;
}
