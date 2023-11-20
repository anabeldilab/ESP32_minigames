#include "../include/position.h"

Position::Position(): x_(1), y_(1) {}

Position::Position(int x, int y): x_(x), y_(y) {}
  
int Position::get_x(void) const { 
  return x_; 
}
int Position::get_y(void) const { 
  return y_; 
}

void Position::set_x(const int& kNewX) {
  x_ = kNewX;
}
void Position::set_y(const int& kNewY) {
  y_ = kNewY;
}

bool Position::operator==(const Position& kOtherPosition) {
  return ((x_ == kOtherPosition.get_x()) && 
           y_ == kOtherPosition.get_y());
}

bool Position::operator!=(const Position& kOtherPosition) {
  return ((x_ != kOtherPosition.get_x()) || 
           y_ != kOtherPosition.get_y());
}

Position Position::operator+(const Position& kOtherPosition) {
  Position result;
  result.set_x(kOtherPosition.get_x() + x_);
  result.set_y(kOtherPosition.get_y() + y_);
  return result;
}