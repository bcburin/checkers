#ifndef CHECKERS_PLAYER_H
#define CHECKERS_PLAYER_H

#include "board.h"
#include <string>
#include <iostream>


namespace Checkers {

  class Player {
    protected:
      std::string name_;
      Piece::ColorType piece_color_;
      Board& board_;
      int num_pieces_;
    public:
      Player(std::string name, Piece::ColorType pc, Board& b)
      : name_(name), piece_color_(pc), board_(b) {}
      
      std::string name() const { return name_; }
      
      Piece::ColorType piece_color() const { return piece_color_; }

      int num_pieces() const { return num_pieces_; }

      void add_piece(int n = 1) { num_pieces_ += n; }
      
      void remove_piece(int n = 1) { num_pieces_ = (n > num_pieces_) ? 0 : (num_pieces_ - n); }
      
      virtual typename Board::Move get_move() const = 0;
  };

};

#endif