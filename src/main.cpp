#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "game.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;


int main() {
  Checkers::Board board;

  // board.print(cout, true);

  // board.move("c3", "d4");
  // board.move("d6", "e5");
  // board.move("e5", "c3");
  // board.move("d2", "b4");
  // board.move("b6", "c5");
  // board.move("b4", "d6");
  // board.move("e7", "c5");

  // bool first_time = true;

  // while(true) {

  //   if(system("CLS")) system("clear");
  //   board.print();

  //   string src, dest;
  //   cout << endl << "Move: ";
  //   cin >> src >> dest;

  //   board.move(src, dest);

  // }
 
  // board.print();

  Checkers::Game game(Checkers::Game::Type::Human_Human);

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