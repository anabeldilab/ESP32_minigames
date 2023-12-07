#include <iostream>

#include "../include/board.h"
#include "../include/square.h"
#include "../include/snake.h"
#include "../include/directedPosition.h"
#include "../include/vector.h"
#include "../include/displayManager.h"

Board::Board() : width_(0), height_(0), 
  board_(new Vector<Vector<Square>>()), snake_(new Snake(this)) {}


Board::Board(const int& kWidth, const int& kHeight) 
  : width_(kWidth), height_(kHeight), 
  board_(new Vector<Vector<Square>>(height_)), 
  snake_(new Snake(this)) {
  srand(time(0));
  for (int i = 0; i < height_; i++) {
    (*board_)[i] = Vector<Square>(width_);
    for (int j = 0; j < width_; j++) {
      (*board_)[i][j] = Square(new DirectedPosition(i, j));
      changeSnakeSquare(DirectedPosition(i, j));
    }
  }
  generateFood();
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


Square& Board::get_square(const DirectedPosition& kDirectedPosition) {
  return (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()];
}


bool Board::isBorder(const DirectedPosition& kDirectedPosition) const {
  return (kDirectedPosition.get_y() == -1 || kDirectedPosition.get_y() == height_ || 
          kDirectedPosition.get_x() == -1 || kDirectedPosition.get_x() == width_);
}


// TODO: Put an enum here
void Board::turnGame(const int& kDirection) {
  moveSnake(kDirection);
  changeSnakeSquare();
}


void Board::moveSnake(const int& kDirection) {
  snake_->move(kDirection);
}


void Board::consumeFood(const DirectedPosition& kDirectedPosition) {
  (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()].setFood(false);
}


void Board::generateFood() {
  int y = rand() % height_;
  int x = rand() % width_;
  while ((*board_)[y][x].isSnakeBody()) {
    y = rand() % height_;
    x = rand() % width_;
  }
  (*board_)[y][x].setFood(true);
}


void Board::gameOver() {
  std::cout << "Game Over" << std::endl;
  exit(0);
}


const Vector<Square>& Board::operator[](const int& kIndex) const {
  if (kIndex < 0 || kIndex >= (*board_).size()) {
    throw std::out_of_range("Row index out of range");
  }
  return (*board_)[kIndex];
}


Vector<Square>& Board::operator[](const int& kIndex) {
  if (kIndex < 0 || kIndex >= (*board_).size()) {
    throw std::out_of_range("Row index out of range");
  }
  return (*board_)[kIndex];
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


/*
void displayBoard(DisplayManager& manager, const Board& kBoard) {
  for (int i = -1; i < kBoard.get_height() + 1; i++) {
    for (int j = -1; j < kBoard.get_width() + 1; j++) {
      manager.drawBorder(DirectedPosition(i + 1, j + 1), kBoard);
      if (kBoard[i][j].isFood()) {
        manager.drawPixel(DirectedPosition(i + 1, j + 1));
      } else if (kBoard[i][j].isSnakeHead()) {
        manager.drawPixel(DirectedPosition(i + 1, j + 1));
      } else if (kBoard[i][j].isSnakeBody()) {
        manager.drawPixel(DirectedPosition(i + 1, j + 1));
      }
    }
  }
}
*/

void Board::changeSnakeSquare() {
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      (*board_)[i][j].setSnakeHead(false);
      (*board_)[i][j].setSnakeBody(false);
      if (snake_->isHead(DirectedPosition(i, j))) {
        (*board_)[i][j].setSnakeHead(true);
        (*board_)[i][j].setSnakeBody(true);
      }
      else if (snake_->isBody(DirectedPosition(i, j))) {
        (*board_)[i][j].setSnakeBody(true);
      }
    }
  }
}


void Board::clean() {
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      (*board_)[i][j].setSnakeHead(false);
      (*board_)[i][j].setSnakeBody(false);
    }
  }
}


void Board::changeSnakeSquare(const DirectedPosition& kDirectedPosition) {
  if (snake_->isHead(kDirectedPosition)) {
    (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()].setSnakeHead(true);
    (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()].setSnakeBody(true);
  }
  else if (snake_->isBody(kDirectedPosition)) {
    (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()].setSnakeBody(true);
  }
}