#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"
#include <iostream>

namespace Checkers {

  class HumanPlayer: public Player {
    private:
      std::istream& is;
    public:
      HumanPlayer(std::string name, Piece::ColorType pc, Board& b, std::istream& is)
      : Player(name, pc, b), is(is) {}
      typename Board::Move get_move() const override;
  };

};

#endif