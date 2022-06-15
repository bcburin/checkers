#include "game.h"

Checkers::Game::Game(Type type, Piece::ColorType p1_color) {
  Piece::ColorType p2_color = (p1_color == Piece::ColorType::dark) ? 
                              Piece::ColorType::light :
                              Piece::ColorType::dark;
  switch(type) {
    case Type::Human_Human:
      player1 = new HumanPlayer("Player 1", p1_color, board_, std::cin);
      player2 = new HumanPlayer("Player 2", p2_color, board_, std::cin);
      break;
    case Type::Human_AI:
      player1 = new HumanPlayer("Player", p1_color, board_, std::cin);
      player2 = new AIPlayer("AI", p2_color, board_);
      break;
    case Type::AI_AI:
      player1 = new AIPlayer("AI 1", p1_color, board_);
      player2 = new AIPlayer("AI 2", p2_color, board_);
      break;
  }

  current = (p1_color == Piece::ColorType::dark) ? player1 : player2;
}

Checkers::Game::~Game() {
  delete player1;
  delete player2;
}

bool Checkers::Game::finished() {
  return player1->num_pieces() == 0 || player2->num_pieces() == 0;
}

void Checkers::Game::play() {
  Board::Move move = current->get_move();
  // Validate piece colour
  if(move.source().piece() && move.source().piece()->color() != current->piece_color())
    throw std::invalid_argument("Invalid piece, you must move one of your own!"); 
  // Perform movement
  move.perform();
  next_player();
}