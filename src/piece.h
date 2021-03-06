#ifndef CHECKERS_PIECE_H
#define CHECKERS_PIECE_H

#include "color.h"
#include <ostream>
#include <string>


using std::ostream;


namespace Checkers {

  class Piece {
    public:
      enum class ColorType { dark, light };
      enum class DirectionType { up, down };
    protected:
      ColorType color_;
    public:
      Piece(ColorType color): color_(color) {}
      ColorType color() const { return color_; }
      DirectionType direction() const { return color_ == ColorType::dark ? DirectionType::up : DirectionType::down; }
      COLOR16 color_w32() const { return color_ == ColorType::dark ? DARK_PIECE_COLOR : LIGHT_PIECE_COLOR; }
      virtual Piece* copy() const = 0;
      virtual std::string str() const = 0;
      virtual bool allows_backwards() const = 0;
      virtual bool allows_bishop_movement() const = 0;      
  };

};

ostream& operator<< (ostream& os, const Checkers::Piece* piece);

#endif