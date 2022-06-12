#include "board.h"

#include <iostream>

typename Checkers::Board::Spot& Checkers::Board::Spot::operator<< (Spot& other) { 
  if(!Move(other, *this).valid()) throw std::invalid_argument("Invalid movement!");
  remove_piece(); 
  piece_ = other.retrive_piece(); 
  return *this; 
}

typename Checkers::Board::Spot& Checkers::Board::Spot::operator>> (Spot& other) { 
  if(!Move(*this, other).valid()) throw std::invalid_argument("Invalid movement!");
  other.remove_piece(); 
  other.piece_ = retrive_piece(); 
  return other; 
}

typename Checkers::Board::Spot& Checkers::Board::Spot::operator= (const Spot& other) { 
  x_ = other.x_; 
  y_ = other.y_; 
  remove_piece();
  piece_ = other.piece_->copy(); 
  return *this;
}

typename Checkers::Board::Spot& Checkers::Board::Spot::operator= (Spot&& other) { 
  x_ = other.x_; 
  y_ = other.y_; 
  remove_piece();
  piece_ = other.retrive_piece();
  return *this;
}

Checkers::Board::Board() {
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

ostream& operator<< (ostream& os, Checkers::Board& board) {
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


ostream& operator<< (ostream& os, const typename Checkers::Board::Spot& spot) {
  return os << (char)('a' + spot.x()) << (spot.y() + 1);
}


ostream& operator<< (ostream& os, const typename Checkers::Board::Move& move) {
  return os << move.source() << " -> " << move.dest();
}

bool Checkers::Board::Move::valid() const {
  if(!is_diagonal()) return false;
  if(!dest().empty()) return false;
  if(source().empty()) return false;

  if(!source().piece()->allows_backwards() && backwards()) return false;

  if(!source().piece()->allows_bishop_movement() && abs(y_delta()) != 1) return false;

  return true;
}

vector<typename Checkers::Board::Move> Checkers::Board::valid_moves_from(size_t xs, size_t ys) {
  vector<Move> valid_moves;
  Spot source = spot(xs, ys);
  for(int x = 0; x != S; ++x) {
    for(int y = 0; y != S; ++y) {
      Move move(source, spot(x,y));
      if(move.valid()) valid_moves.push_back(move);
    }
  }
  return valid_moves;
}

void Checkers::Board::move(size_t srcx, size_t srcy, size_t dstx, size_t dsty) {
  Spot& source = spot(srcx, srcy);
  Spot& dest = spot(dstx, dsty);
  if(!Move(source, dest).valid()) throw std::invalid_argument("Invalid movement!");
  dest << source;
}
