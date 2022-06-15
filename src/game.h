#ifndef CHECKERS_GAME_H
#define CHECKERS_GAME_H

#include "board.h"
#include "human_player.h"
#include "ai_player.h"

namespace Checkers {

  class Game {
    public:
      enum class Type { Human_Human, Human_AI, AI_AI };
    private:
      Player* player1;
      Player* player2;
      Player* current;
      Board board_;
    public:
      Game(Type type, Piece::ColorType p1_color = Piece::ColorType::dark);
      
      ~Game();
      
      bool finished();
      
      void play();

      Board& board() { return board_; }
      
      void next_player() { current = (current == player1) ? player2 : player1; }
  };

};

#endif