#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "game.h"
#include "color.h"

enum class ModeMenuOption { Human_Human, Human_AI, AI_AI, invalid };
enum class ColorMenuoption { dark, light, invalid };

Checkers::Game::Type get_mode_option();
Checkers::Piece::ColorType get_color_option();
void print_mode_options();
void print_color_options();
void print_border();
void print(std::invalid_argument& error);


int main() {

  // Input game mode
  Checkers::Game::Type mode;
  print_mode_options();
  bool valid_input = false;
  while(!valid_input) {
    try { mode = get_mode_option(); valid_input = true; } 
    catch (std::invalid_argument& error) { print(error); }
  }

  // Input color (if singleplayer)
  Checkers::Piece::ColorType color = Checkers::Piece::ColorType::dark;
  if(mode == Checkers::Game::Type::Human_AI) {
    print_color_options();
    valid_input = false;
    while(!valid_input) {
      try { color = get_color_option(); valid_input = true; } 
      catch(std::invalid_argument& error) { print(error); }
    }
  }

  // Create game
  Checkers::Game game(mode, color);

  // Game loop
  while(!game.finished()) {
    game.board().print();
    valid_input = false;
    while(!valid_input) {
      try { game.play(); valid_input = true; }
      catch(std::invalid_argument& error) { print(error); }
    }
  }

  return EXIT_SUCCESS;
}


void print_mode_options() {
  clear_console();
  set_color(WRITING_COLOR);
  print_border();
  std::cout << "How many players?" << std::endl << std::endl;
  std::cout << "    1 - Single player" << std::endl;
  std::cout << "    2 - Multi player" << std::endl;
  std::cout << "    3 - No player (match of two AIs)" << std::endl;
  print_border();
  reset_color();
}

void print_color_options() {
  clear_console();
  set_color(WRITING_COLOR);
  print_border();
  std::cout << "What color will you play?" << std::endl << std::endl;
  std::cout << "    1 - Blue (blacks)" << std::endl;
  std::cout << "    2 - Red (whites)" << std::endl;
  print_border();
  reset_color();
}

Checkers::Game::Type get_mode_option() {
  set_color(WRITING_COLOR);
  // Get choice
  int op;
  std::cout << "Your choice: ";
  std::cin >> op;
  reset_color();
  // Interpret input
  switch(op) {
    case 1: return Checkers::Game::Type::Human_AI;
    case 2: return Checkers::Game::Type::Human_Human;
    case 3: return Checkers::Game::Type::AI_AI;
  }
  // Invalid input
  throw std::invalid_argument("Invalid input!");
}

Checkers::Piece::ColorType get_color_option() {
  set_color(WRITING_COLOR);
  // Get choice
  int op;
  std::cout << "Your choice: ";
  std::cin >> op;
  reset_color();
  // Interpret input
  switch(op) {
    case 1: return Checkers::Piece::ColorType::dark;
    case 2: return Checkers::Piece::ColorType::light;
  }
  // Invalid input
  throw std::invalid_argument("Invalid input!");
}

void print(std::invalid_argument& error) {
  set_color(WRITING_COLOR);
  std::cerr << std::endl << error.what() << std::endl << std::endl;
  reset_color();
}

void print_border() { std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl; }
