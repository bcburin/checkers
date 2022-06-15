#include "ai_player.h"
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typename Checkers::Board::Move Checkers::AIPlayer::get_move() const {
  srand(time(NULL));

  #ifdef _WIN32
  Sleep(1000);
  #else
  usleep(1000);
  #endif

  std::vector<Board::Move> all_valid_moves;

  for(int x = 0; x != S; ++x) {
    for(int y = 0; y != S; ++y) {
      auto& curr = board_.spot(x, y);
      // Check if piece at (x, y) is controlled by AI
      if(curr.piece() &&  curr.piece()->color() == piece_color_) {
        auto valid_moves = board_.valid_moves_from(x, y);
        if(valid_moves.empty()) continue;
        // Return the first valid move that killed a piece, if there is any
        for(auto& move : valid_moves) if(move.has_killed()) return move;
        // Add current valid moves to all_valid_moves
        for(auto& move : valid_moves) all_valid_moves.push_back(move);
      }
    }
  }
  
  // If no killing move was found, return a random valid move
  if(!all_valid_moves.empty()) 
    return all_valid_moves[ rand() % all_valid_moves.size() ];

  // If there is no valid move, throw locked game exception
  throw std::invalid_argument(name() + std::string("is stuck!"));
}
