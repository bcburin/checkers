#include "board.h"
#include <sstream>

#define FORE_BEIGE (FOREGROUND_RED | FOREGROUND_GREEN)
#define BACK_BEIGE (BACKGROUND_RED | BACKGROUND_GREEN)
#define BACK_BLACK 0

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

void Checkers::Board::Spot::promote_piece() { 
  if(dynamic_cast<Checker*>(piece_)) {
    Piece* promoted_ = new King(piece_->color());
    remove_piece();
    piece_ = promoted_; 
  } 
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
    for(int x = 0; x != S; ++x) {
      set_color(board.spot(x,y).color_w32());
      os << "       ";
    }
    os << std::endl;
    for(int x = 0; x != S; ++x) {
      auto piece = board.spot(x,y).piece();
      set_color(board.spot(x,y).color_w32() | (piece ? piece->color_w32() : 0));
      os << "   " << piece << "   ";
    }
    set_color(WRITING_COLOR);
    os << "   " << y+1 << std::endl;
    for(int x = 0; x != S; ++x) {
      set_color(board.spot(x,y).color_w32());
      os << "       ";
    }
    os << std::endl;
  }
  os << std::endl;
  set_color(WRITING_COLOR);
  for(int x = 0; x != S; ++x) os << "   " << (char)('a'+x) << "   ";
  os << std::endl;
  reset_color();
  return os;
}

ostream& operator<< (ostream& os, const typename Checkers::Board::Spot& spot) {
  return os << (char)('a' + spot.x()) << (spot.y() + 1);
}

ostream& operator<< (ostream& os, const typename Checkers::Board::Move& move) {
  return os << move.source() << " -> " << move.dest();
}

void Checkers::Board::Move::check_kill() {
  // Check for piece to kill
  if(source_.piece() && source_.piece()->allows_bishop_movement() && is_diagonal()) {
    Spot& next_spot = board_.delta(dest_, -x_delta()/2, -y_delta()/2);
    if(next_spot.piece() && next_spot.piece()->color() != source_.piece()->color()) 
      killed_ = &next_spot;
  }
  else if(abs(x_delta()) == 2 && abs(y_delta()) == 2) {
    Spot& next_spot = board_.delta(source_, x_delta()/2, y_delta()/2);
    if(next_spot.piece() && next_spot.piece()->color() != source_.piece()->color()) 
      killed_ = &next_spot;
  }
}

void Checkers::Board::Move::validate() {
  if(source_.empty()) throw std::invalid_argument("No piece to move!");
  if(!dest_.empty()) throw std::invalid_argument("Destiny spot not empty!");
  if(!is_diagonal()) throw std::invalid_argument("Movement must be diagonal!");

  if(!source_.piece()->allows_backwards() && backwards()) throw std::invalid_argument("That piece cannot move backwards!");

  check_kill();
  if(killed_) return;

  if(!source_.piece()->allows_bishop_movement() && abs(y_delta()) != 1) throw std::invalid_argument("That piece cannot move more than one diagonal unit!");
}

void Checkers::Board::Move::perform() {
  // Perform movement
  validate();
  source_ >> dest_;
  kill();
  // Promote piece, if necessary
  if((dest_.piece()->color() == Piece::ColorType::dark && dest_.y() == S-1) ||
     (dest_.piece()->color() == Piece::ColorType::light && dest_.y() == 0) ) {
    dest_.promote_piece();
  }
}

vector<typename Checkers::Board::Move> Checkers::Board::valid_moves_from(size_t xs, size_t ys) {
  vector<Move> valid_moves;
  Spot& source = spot(xs, ys);
  for(int x = 0; x != S; ++x) {
    for(int y = 0; y != S; ++y) {
      Move move(source, spot(x,y), *this);
      try {
        move.validate();
        valid_moves.push_back(move);
      } catch(std::invalid_argument& e) { /* Do nothing */ }
    }
  }
  return valid_moves;
}

typename Checkers::Board::Spot& Checkers::Board::spot(std::string pos) {
  if(pos.size() != 2) 
    throw std::invalid_argument("Position must given in algebraic notation by one character and one letter: e.g. c5.");
  size_t x = (pos[0]-'a');
  size_t y = (pos[1]-'1');
  return spot(x, y);
}
