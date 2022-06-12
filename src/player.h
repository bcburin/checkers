#ifndef CHECKERS_PLAYER_H
#define CHECKERS_PLAYER_H

#include "board.h"
#include <string>
#include <iostream>


namespace Checkers {

  class Player {
    public:
      enum class PieceColorType { dark, light };
    protected:
      std::string name_;
      PieceColorType piece_color_;
      Board& board_;
    public:
      Player(std::string name, PieceColorType pc, Board& b)
      : name_(name), piece_color_(pc), board_(b) {}
      
      std::string name() const { return name_; }
      
      PieceColorType piece_color() const { return piece_color_; }
      
      virtual typename Board::Move get_move() const = 0;
  };

};

#endif