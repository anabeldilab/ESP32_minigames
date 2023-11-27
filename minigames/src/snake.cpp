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


bool Snake::CheckFood() const {
  if (board_->get_square(head_directed_position_->nextPosition()).isFood()) {
    return true;
  }
  return false;
}


bool Snake::CheckCollision() const {
  if (board_->isBorder(head_directed_position_->nextPosition()) 
      || isBody(head_directed_position_->nextPosition())) {
    return true;
  }
  return false;
}


// TODO: Put an enum here
// TODO: I have two snake heads
void Snake::Move(const int& direction) {
  //std::cout << "is border: " << head_directed_position_->nextPosition() << std::endl;
  if (CheckFood()) {
    Grow();
    board_->generateFood();
  } else if (CheckCollision()) {
    board_->gameOver();
  } else {
    ChangeDirection(direction);
    MoveBody();
  }
}


// TODO snake can't grow if it's on the border
void Snake::Grow() {
  if (body_size_ == 1) {
    body_.push_back(*head_directed_position_);
  } else {
    body_.push_back(body_[body_size_ - 1]);
  } 
  body_size_++;
  body_.push_back(body_[body_size_ - 2]);
}


void Snake::ChangeDirection(const int& direction) {
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

// TODO: revision
void Snake::MoveBody() {
  DirectedPosition temp = *head_directed_position_;
  for (int i = 0; i < body_size_; i++) {
    DirectedPosition temp2 = body_[i];
    body_[i] = temp;
    temp = temp2;
  }
  head_directed_position_->turnDirection(head_directed_position_->get_direction());
  head_directed_position_->set_x(head_directed_position_->nextPosition().get_x());
  head_directed_position_->set_y(head_directed_position_->nextPosition().get_y());
}


// TODO: delete
bool Snake::get_body_size(void) const {
  return body_size_;
}