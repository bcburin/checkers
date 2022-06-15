#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "game.h"


int main() {
  Checkers::Board board;

  Checkers::Game game(Checkers::Game::Type::Human_AI);

  while(!game.finished()) {
    bool valid_move = false;
    if(system("CLS")) system("clear");
    game.board().print();
    while(!valid_move) {
      try {
        game.play();
        game.next_player();
        valid_move = true;
      } catch(std::invalid_argument& error) {
        std::cerr << std::endl << error.what() << std::endl;
      }
    }
  }

  return 0;
}