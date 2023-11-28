#include "../include/snake.h"
#include "../include/directedPosition.h"
#include "../include/board.h"
#include "../include/square.h"

// Snake::Snake() TODO random position 

Snake::Snake(Board* board, DirectedPosition* position) 
  : board_(board), 
    body_size_(1), 
    body_(std::vector<DirectedPosition>(body_size_, *position)),
    head_directed_position_(position), 
    delete_position_(false) {}


Snake::Snake(Board* board) 
  : board_(board), 
    body_size_(1), 
    body_(std::vector<DirectedPosition>(body_size_)),
    head_directed_position_(new DirectedPosition()), 
    delete_position_(true) {}


Snake::~Snake() {
  if (delete_position_) {
    delete head_directed_position_;
  }
}


bool Snake::isHead(const DirectedPosition& kPosition) const {
  return *head_directed_position_ == kPosition;
}


bool Snake::isBody(const DirectedPosition& kPosition) const {
  for (int i = 0; i < body_size_; i++) {
    if (body_[i] == kPosition) {  
      return true;
    }
  }
  return false;
}


bool Snake::checkFood() const {
  if (board_->get_square(head_directed_position_->nextPosition()).isFood()) {
    return true;
  }
  return false;
}


bool Snake::checkCollision() const {
  if (board_->isBorder(head_directed_position_->nextPosition()) 
      || isBody(head_directed_position_->nextPosition())) {
    return true;
  }
  return false;
}


// TODO: Put an enum here
void Snake::move(const int& direction) {
  changeDirection(direction);
  if (checkCollision()) {
    board_->gameOver();
  } if (checkFood()) {
    board_->consumeFood(head_directed_position_->nextPosition());
    grow();
    board_->generateFood();
  }
  moveBody();
}


void Snake::grow() {
  body_size_++;
  body_.push_back(body_.back());
}


void Snake::changeDirection(const int& direction) {
  if (direction == Up) {
    head_directed_position_->turnDirection(Up);
  } else if (direction == Down) {
    head_directed_position_->turnDirection(Down);
  } else if (direction == Left) {
    head_directed_position_->turnDirection(Left);
  } else {
    head_directed_position_->turnDirection(Right);
  }

}


void Snake::moveBody() {
  moveHead();
  DirectedPosition bodySegmentPositionUpdate = *head_directed_position_;
  for (int i = 0; i < body_size_; i++) {
    DirectedPosition bodySegmentPositionBeforeUpdate = body_[i];
    body_[i] = bodySegmentPositionUpdate;
    bodySegmentPositionUpdate = bodySegmentPositionBeforeUpdate;
  }
}


void Snake::moveHead() {
  head_directed_position_->turnDirection(head_directed_position_->get_direction());
  head_directed_position_->set_x(head_directed_position_->nextPosition().get_x());
  head_directed_position_->set_y(head_directed_position_->nextPosition().get_y());
}


// TODO: delete
bool Snake::get_body_size(void) const {
  return body_size_;
}