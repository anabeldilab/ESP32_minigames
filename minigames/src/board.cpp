#include "../include/board.h"
#include "../include/snake.h"
#include "../include/position.h"
#include "../include/square.h"

Board::Board() : width_(0), height_(0), 
  board_(std::vector<std::vector<Square>>()), snake_(new Snake(this)) {} // TODO check if this is correct


Board::Board(const int& kHeight, const int& kWidth) 
  : width_(kWidth), height_(kHeight), 
  board_(std::vector<std::vector<Square>>(kHeight, std::vector<Square>(kWidth))), 
  snake_(new Snake(this)) {
  for (int i = 0; i < kHeight; i++) {
    for (int j = 0; j < kWidth; j++) {
      board_[i][j] = Square(new Position(i, j));
      if (snake_->isHead(Position(i,j))) {
        board_[i][j].setSnakeHead(true);
        board_[i][j].setSnakeBody(true);
      } else if (snake_->isBody(Position(i,j))) {
        board_[i][j].setSnakeBody(true);
      }
    }
  }

}


Board::~Board() {
  delete snake_;
}


int Board::get_width(void) const {
  return width_;
}


int Board::get_height(void) const {
  return height_;
}


Snake* Board::get_snake(void) const {
  return snake_;
}


Square& Board::get_square(const Position& kPosition) {
  return board_[kPosition.get_x()][kPosition.get_y()];
}


bool Board::isBorder(const Position& kPosition) const {
  return (kPosition.get_x() == 0 || kPosition.get_x() == height_ + 1 || 
          kPosition.get_y() == 0 || kPosition.get_y() == width_ + 1);
}


const std::vector<Square>& Board::operator[](const int& kIndex) const {
  if (kIndex < 0 || kIndex >= board_.size()) {
    throw std::out_of_range("Row index out of range");
  }
  return board_[kIndex];
}


std::vector<Square>& Board::operator[](const int& kIndex) {
  if (kIndex < 0 || kIndex >= board_.size()) {
    throw std::out_of_range("Row index out of range");
  }
  return board_[kIndex];
}


std::ostream& operator<<(std::ostream& os, const Board& kBoard) {
  for (int i = -1; i < kBoard.get_height() + 1; i++) {
    for (int j = -1; j < kBoard.get_width() + 1; j++) {
      if (i == -1 || i == kBoard.get_height() || 
          j == -1 || j == kBoard.get_width()) {
          os << "🧱";
      } else {
        os << kBoard[i][j];
      }
    }
    os << std::endl;
  }
  return os;
}
