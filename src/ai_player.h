#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "player.h"

namespace Checkers {
  
  class AIPlayer: public Player {
    public:
      AIPlayer(std::string name, Piece::ColorType pc, Board& b): Player(name, pc, b) {}
      typename Board::Move get_move() const override;
  };

};

#endif