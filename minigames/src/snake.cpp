#include "../include/snake.h"
#include "../include/position.h"
#include "../include/board.h"

Snake::Snake(Board* board, Position* position) : 
  board_(board), body_size_(1), body_(new Position*(position)), head_position_(position), 
  next_head_position_(new Position(head_position_->get_x() + 1, head_position_->get_y())), delete_position_(false) {}

Snake::Snake(Board* board) : board_(board), body_size_(1), body_(new Position*(new Position())),
  head_position_(new Position()), 
  next_head_position_(new Position(head_position_->get_x() + 1, head_position_->get_y())), delete_position_(true) {}

Snake::~Snake() {
  for (int i = 0; i < body_size_; i++) {
    delete body_[i];
  }
  delete[] body_;
  if (delete_position_) {
    delete head_position_;
  }
  delete next_head_position_;
}


bool Snake::isHead(const Position& kPosition) const {
  return *head_position_ == kPosition;
}


bool Snake::isBody(const Position& kPosition) const {
  for (int i = 0; i < body_size_; ++i) {
    if (*body_[i] == kPosition) {  
      return true;
    }
  }
  return false;
}


bool Snake::CheckFood() {
  // TODO
  return false;
}


bool Snake::CheckCollision() {
  // TODO
  return false;
}