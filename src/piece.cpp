#include "piece.h"

ostream& operator<< (ostream& os, const Checkers::Piece* piece) {
  if(!piece) os << "  ";
  else os << piece->str();
  return os;
}