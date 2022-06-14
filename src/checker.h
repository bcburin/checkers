#ifndef CHECKERS_CHECKER_H
#define CHECKERS_CHECKER_H

#include "piece.h"


namespace Checkers {
  
  class Checker : public Piece {
    public: 
      Checker(Piece::ColorType color): Piece(color) {}
      Checker* copy() const override { return new Checker(color_); };
      bool allows_backwards() const override { return false; }
      bool allows_bishop_movement() const override { return false; }
      std::string str() const override { return (color() == ColorType::dark) ? "* " : "+ "; }
  };

};

#endif