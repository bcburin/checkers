#ifndef CHECKERS_BOARD_H
#define CHECKERS_BOARD_H

#include <utility>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cmath>

#include "piece.h"
#include "checker.h"
#include "king.h"

#define S 8
// #define DELETE_ANSI "\x1b[17A"

using std::ostream;
using std::vector;
using std::abs;

namespace Checkers {

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

          Spot(const Spot& other): Spot(other.x_, other.y_, other.piece_ ? other.piece_->copy() : nullptr) { }
          Spot(Spot&& other): Spot(other.x_, other.y_, other.piece_) { other.piece_ = nullptr; }

          ~Spot() { remove_piece(); }

          Spot& operator= (const Spot& other);
          Spot& operator= (Spot&& other);

          /*  Removes piece from other spot and stores it in current spot;
           *  Returns current spot (allows chaining).
           */
          Spot& operator<< (Spot& other);

          /*  Removes piece from current spot and stores it in other spot;
           *  Returns other spot (allows chaining).
           */
          Spot& operator>> (Spot& other);

          /* Two spots are equal if they have the same coordinates;
           * The pieces each of them hold are irrelevant for equality.
           */
          bool operator== (const Spot& other) const { return x_ == other.x_ && y_ == other.y_; }

          bool allowed() const { return color() == ColorType::dark; }

          bool empty() const { return piece_ == nullptr; }

          bool occupied() const { return !empty(); }

          int x() const { return (int)x_; }
          int y() const { return (int)y_; }

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

          void promote_piece();
      };

      class Move {
        public:
          enum class DirectionType { forward, backwards };
        private:
          Spot& source_;
          Spot& dest_;

          Spot* killed_;

          Board& board_;
        
        public:
          Move(Spot& s, Spot& d, Board& b): source_(s), dest_(d), killed_(nullptr), board_(b) { }

          int x_delta() const { return dest_.x() - source_.x(); }
          
          int y_delta() const { return dest_.y() - source_.y(); }
          
          bool is_horizonatal() const { return source_.y() == dest_.y(); }
          
          bool is_vertical() const { return source_.x() == dest_.x(); }

          bool is_diagonal() const { 
            // Two spots are on the same diagonal iff the sum or difference of their indexes are equal
            return source_.y() - source_.x() == dest_.y() - dest_.x() ||
                   source_.y() + source_.x() == dest_.y() + dest_.x();
          }
          
          DirectionType direction() const { 
            return (source_.piece()->direction() == Piece::DirectionType::up) ?
                   (y_delta() > 0 ? DirectionType::forward : DirectionType::backwards) :
                   (y_delta() < 0 ? DirectionType::forward : DirectionType::backwards);
          }

          bool forwards() const { return direction() == DirectionType::forward; }

          bool backwards() const { return direction() == DirectionType::backwards; }

          Spot source() const { return source_; }
          
          Spot dest() const { return dest_; }
          
          void validate();

          void check_kill();
          
          void kill() { if(killed_) killed_->remove_piece(); }
          
          void perform();
      };

    private:

      Spot spot_[S][S];

    public:

      Board();

      // TODO: validate input
      Spot& spot(size_t x, size_t y) { return spot_[x][y]; }

      // TODO: validate input
      Spot& spot(std::string pos);

      /* Returns reference to the spot dx units up and dy units right
       * Allows negative and posive deltas from src
       * TODO: validate input
       */
      Spot& delta(Spot& src, int dx, int dy) { return spot(src.x() + dx, src.y() + dy); }

      // TODO: validate input
      vector<Move> valid_moves_from(size_t x, size_t y);

      void print(ostream& os = std::cout, bool first_time = false);

  };

};


ostream& operator<< (ostream&, Checkers::Board&);

ostream& operator<< (ostream&, const typename Checkers::Board::Spot&);

ostream& operator<< (ostream&, const typename Checkers::Board::Move&);

#endif