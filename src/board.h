#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include <utility>
#include <stdexcept>
#include <ostream>
#include <vector>

#include "piece.h"
#include "checker.h"
#include "king.h"

using std::ostream;
using std::vector;

namespace Checkers {

  template <size_t S>
  class Board {
    public:

      class Spot {
        public:
          enum class ColorType { dark, light };
        private:
          size_t x_, y_;

          Piece* piece_;

          /* Checks validity of spot coordinates;
           * 
           */
          bool valid() { return 0 <= x_ && x_ < S && 0 <= y_ && y_ < S; }

        public:
          Spot(size_t x=1, size_t y=1, Piece* piece = nullptr)
          : x_(x), y_(y), piece_(piece) { if (!valid()) throw std::out_of_range("Board spot out of bounds"); }

          Spot(const Spot& other): Spot(other.x_, other.y_, other.piece_->copy()) {}
          Spot(Spot&& other): Spot(other.x_, other.y_, other.piece_) { other.piece_ = nullptr; }

          ~Spot() { remove_piece(); }

          Spot& operator= (const Spot& other);
          Spot& operator= (Spot&& other);

          /*  Removes piece from other spot and stores it in current spot;
           *  Returns current spot (allows chaining).
           */
          Spot& operator<< (Spot& other) { remove_piece(); piece_ = other.retrive_piece(); return *this; }

          /*  Removes piece from current spot and stores it in other spot;
           *  Returns other spot (allows chaining).
           */
          Spot& operator>> (Spot& other) { other.remove_piece(); other.piece_ = retrive_piece(); return other; }

          /* Two spots are equal if they have the same coordinates;
           * The pieces each of them hold are irrelevant for equality.
           */
          bool operator== (const Spot& other) { return x_ == other.x_ && y == other.y_; }

          bool allowed() const { return color() == ColorType::dark; }

          size_t x() const { return x_; }
          size_t y() const { return y_; }

          /* Returns color of currrent spot, which only depends on the coordinates.
           */
          ColorType color() const { return (x_%2 == y_%2) ? ColorType::dark : ColorType::light; } 

          Piece* piece() const { return piece_; }

          /* Removes piece from current spot;
           * Returns pointer to removed piece.
           */
          Piece* retrive_piece() { auto buffer = piece_; piece_ = nullptr; return buffer; }

          /* Removes from current spot and deallocates its memory;
           * Returns reference to current spot (allows chaining).
           */
          Spot& remove_piece() { if(piece_) delete piece_; piece_ = nullptr; return *this; }

          /* Inserts given piece to spot;
           * Pice needs to have been previously dynamicallt allocated;
           * Returns referentce to current spot (allows chaining).
           */
          Spot& insert_piece(Piece* piece) { remove_piece(); piece_ = piece; return *this; }
      };

      class Move {
        private:
          Spot& source_;
          Spot& dest_;
        public:
          Move(Spot& s, Spot& d): source_(s), dest_(d) {}
          Spot& source() { return source_; }
          Spot& dest() { return dest_; }
          bool valid();
      };

    private:

      Spot spot_[S][S];

    public:

      Board();

      // TODO: validate input
      Spot& spot(size_t x, size_t y) { return spot_[x][y]; }


  };

};


template <size_t S> ostream& operator<< (ostream&, Checkers::Board<S>&);


/* TEMPLATE IMPLEMENTATIONS */

template <size_t S> typename Checkers::Board<S>::Spot& Checkers::Board<S>::Spot::operator= (const Spot& other) { 
  x_ = other.x_; 
  y_ = other.y_; 
  remove_piece();
  piece_ = other.piece_->copy(); 
  return *this;
}

template <size_t S> typename Checkers::Board<S>::Spot& Checkers::Board<S>::Spot::operator= (Spot&& other) { 
  x_ = other.x_; 
  y_ = other.y_; 
  remove_piece();
  piece_ = other.retrive_piece();
  return *this;
}

template <size_t S> Checkers::Board<S>::Board() {
  for(int x = 0; x != S; ++x) {
    for(int y = 0; y!= S; ++y) {
      spot_[x][y] = Spot(x,y);
      if(y < 3 && spot_[x][y].allowed()) 
        spot_[x][y].insert_piece(new Checker(Piece::ColorType::dark));
      if(y >= S-3 && spot_[x][y].allowed())
        spot_[x][y].insert_piece(new Checker(Piece::ColorType::light));
    }
  }
}


template <size_t S> ostream& operator<< (ostream& os, Checkers::Board<S>& board) {
  for(int y = S-1; y != -1; --y) {
    if(y == S-1) {
      for(int x = 0; x != S; ++x) os << (x ? "-" : "|-") << "-" << "-|";
      os << std::endl;
    }
    for(int x = 0; x != S; ++x) os << (x ? " " : "| ") << board.spot(x,y).piece() << " |";
    os << std::endl;
    for(int x = 0; x != S; ++x) os << (x ? "-" : "|-") << "-" << "-|";
    os << std::endl;
  }
  return os;
}


#endif