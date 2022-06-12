#include "piece.h"

ostream& operator<< (ostream& os, const Checkers::Piece* piece) {
  if(!piece) os << " ";
  else os << (piece->color() == Checkers::Piece::ColorType::dark ? "D" : "L");
  return os;
}