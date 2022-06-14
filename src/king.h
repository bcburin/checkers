#ifndef CHECKERS_KING_H
#define CHECKERS_KING_H

#include "piece.h"

namespace Checkers {

  class King: public Piece {
    public:
      King(Piece::ColorType color): Piece(color) {}
      King* copy() const override { return new King(color_); };
      bool allows_backwards() const override { return true; }
      bool allows_bishop_movement() const override { return true; }
      std::string str() const override { return (color() == ColorType::dark) ? "**" : "++"; }
  };

};

#endif