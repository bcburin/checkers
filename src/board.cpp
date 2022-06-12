#include "board.h"
#include <sstream>

typename Checkers::Board::Spot& Checkers::Board::Spot::operator<< (Spot& other) { 
  remove_piece(); 
  piece_ = other.retrive_piece(); 
  return *this; 
}

typename Checkers::Board::Spot& Checkers::Board::Spot::operator>> (Spot& other) { 
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

void Checkers::Board::print(ostream& os, bool first_time) {
  os << *this;
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
  if(!dest_.empty()) return false;
  if(source_.empty()) return false;

  if(!source_.piece()->allows_backwards() && backwards()) return false;

  if(killed_) return true;

  if(!source_.piece()->allows_bishop_movement() && abs(y_delta()) != 1) return false;

  return true;
}

void Checkers::Board::Move::perform() {
  source_ >> dest_;
  kill();
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

void Checkers::Board::move(std::string src, std::string des) {
  Move move(spot(src), spot(des));
  // Check for piece to kill
  if(abs(move.x_delta()) == 2 && abs(move.y_delta()) == 2) {
    Spot& next_spot = delta(spot(src), move.x_delta()/2, move.y_delta()/2);
    if(next_spot.piece()) move.set_killed(&next_spot);
  }
  // Perform movement
  if(move.valid()) move.perform();
  else throw std::invalid_argument("Invalid move!");
}

typename Checkers::Board::Spot& Checkers::Board::spot(std::string pos) {
  if(pos.size() != 2) 
    throw std::invalid_argument("Position must given in algebraic notation by one character and one letter: e.g. c5.");
  size_t x = (pos[0]-'a');
  size_t y = (pos[1]-'1');
  return spot(x, y);
}
