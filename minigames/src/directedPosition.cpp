#include <iostream>

#include "../include/directedPosition.h"

DirectedPosition::DirectedPosition()
  : x_(0), 
    y_(0), 
    direction_(Right) {}


DirectedPosition::DirectedPosition(const int& y, const int& x)
  : x_(x), 
    y_(y), 
    direction_(Right) {}


DirectedPosition::DirectedPosition(const int& y, 
                                   const int& x, 
                                   const Direction& kDirection)
  : x_(x), 
    y_(y), 
    direction_(kDirection) {}

  
int DirectedPosition::get_x(void) const { 
  return x_; 
}


int DirectedPosition::get_y(void) const { 
  return y_; 
}


Direction DirectedPosition::get_direction(void) const { 
  return direction_; 
}


void DirectedPosition::set_x(const int& kNewX) {
  x_ = kNewX;
}


void DirectedPosition::set_y(const int& kNewY) {
  y_ = kNewY;
}


void DirectedPosition::turnRight(const Direction& kDirection) {
  if (kDirection == Up) {
    direction_ = Right;
  } else if (kDirection == Right) {
    direction_ = Down;
  } else if (kDirection == Down) {
    direction_ = Left;
  } else {
    direction_ = Up;
  }
}


void DirectedPosition::turnLeft(const Direction& kDirection) {
  if (kDirection == Up) {
    direction_ = Left;
  } else if (kDirection == Left) {
    direction_ = Down;
  } else if (kDirection == Down) {
    direction_ = Right;
  } else {
    direction_ = Up;
  } 
}


void DirectedPosition::turnDirection(const Direction& kDirection) {
  direction_ = kDirection;
}


DirectedPosition DirectedPosition::nextPosition() const {
  DirectedPosition result;
  if (direction_ == Up) {
    result.set_x(x_);
    result.set_y(y_ - 1);
  } else if (direction_ == Down) {
    result.set_x(x_);
    result.set_y(y_ + 1);
  } else if (direction_ == Left) {
    result.set_x(x_ - 1);
    result.set_y(y_);
  } else {
    result.set_x(x_ + 1);
    result.set_y(y_);
  }
  return result;
}


bool DirectedPosition::operator==(const DirectedPosition& kOtherPosition) {
  return ((x_ == kOtherPosition.get_x()) && 
           y_ == kOtherPosition.get_y());
}


bool DirectedPosition::operator!=(const DirectedPosition& kOtherPosition) {
  return ((x_ != kOtherPosition.get_x()) || 
           y_ != kOtherPosition.get_y());
}


DirectedPosition DirectedPosition::operator+(const DirectedPosition& kOtherPosition) {
  DirectedPosition result;
  result.set_x(kOtherPosition.get_x() + x_);
  result.set_y(kOtherPosition.get_y() + y_);
  return result;
}


bool DirectedPosition::operator==(const DirectedPosition& kOtherPosition) const {
  return ((x_ == kOtherPosition.get_x()) && 
           y_ == kOtherPosition.get_y());
}


bool DirectedPosition::operator!=(const DirectedPosition& kOtherPosition) const {
  return ((x_ != kOtherPosition.get_x()) || 
           y_ != kOtherPosition.get_y());
}


DirectedPosition DirectedPosition::operator+(const DirectedPosition& kOtherPosition) const {
  DirectedPosition result;
  result.set_x(kOtherPosition.get_x() + x_);
  result.set_y(kOtherPosition.get_y() + y_);
  return result;
}


std::ostream& operator<<(std::ostream& os, const DirectedPosition& kDirectedPosition) {
  os << "(" << kDirectedPosition.get_x() << ", " << kDirectedPosition.get_y() << ")";
  return os;
}