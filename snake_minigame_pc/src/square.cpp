#include <iostream>

#include "../include/square.h"
#include "../include/directedPosition.h"

Square::Square() 
  : directed_position_(nullptr), 
    food_(false), 
    snake_body_(false), 
    snake_head_(false), 
    delete_position_(true) {}


Square::Square(DirectedPosition* position) 
  : directed_position_(position), 
    food_(false), 
    snake_body_(false), 
    snake_head_(false), 
    delete_position_(false) {}


Square::~Square() {
  if (delete_position_)
    delete directed_position_;
}


bool Square::isSnakeBody() const {
  return snake_body_;
}


bool Square::isSnakeHead() const {
  return snake_head_;
}


bool Square::isFood() const {
  return food_;
}


void Square::setSnakeBody(const bool& kNewSnakeBody) {
  snake_body_ = kNewSnakeBody;
}


void Square::setSnakeHead(const bool& kNewSnakeHead) {
  snake_head_ = kNewSnakeHead;
}


void Square::setFood(const bool& kNewFood) {
  food_ = kNewFood;
}


std::ostream& operator<<(std::ostream& os, const Square& kSquare) {
  if (kSquare.isFood()) {
    os << "🍎";
  } else if (kSquare.isSnakeHead()) {
    os << "🟢";
  } else if (kSquare.isSnakeBody()) {
    os << "🟩";
  } else {
    os << "⬜";
  }
  return os;
}