#include <iostream>

#include "../include/board.h"
#include "../include/snake.h"
#include "../include/directedPosition.h"
#include "../include/vector.h"

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
      (*board_)[i][j] = Empty;
      changeSnakeSquare(i, j);
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


Board::Square Board::get_square(const int& x, const int& y) const {
  return (*board_)[x][y];
}


Board::Square Board::get_square(const DirectedPosition& kDirectedPosition) const {
  return (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()];
}


bool Board::isBorder(const int& x, const int& y) const {
  return (y == -1 || y == width_ || 
          x == -1 || x == height_);
}


bool Board::isFood(const int& x, const int& y) const {
  if (x < 0 || x >= height_ || y < 0 || y >= width_) {
    throw std::out_of_range("Food: Index out of range");
  }
  return (*board_)[x][y] == Food;
}


bool Board::isSnakeBody(const int& x, const int& y) const {
  if (x < 0 || x >= height_ || y < 0 || y >= width_) {
    throw std::out_of_range("SnakeBody: Index out of range");
  }
  return (*board_)[x][y] == SnakeBody;
}


bool Board::isSnakeHead(const int& x, const int& y) const {
  if (x < 0 || x >= height_ || y < 0 || y >= width_) {
    throw std::out_of_range("SnakeHead: Index out of range");
  }
  return (*board_)[x][y] == SnakeHead;
}


bool Board::isBorder(const DirectedPosition& kDirectedPosition) const {
  return (kDirectedPosition.get_y() == -1 || kDirectedPosition.get_y() == height_ || 
          kDirectedPosition.get_x() == -1 || kDirectedPosition.get_x() == width_);
}


bool Board::isFood(const DirectedPosition& kDirectedPosition) const {
  if (kDirectedPosition.get_x() < 0 || kDirectedPosition.get_x() >= width_ || 
      kDirectedPosition.get_y() < 0 || kDirectedPosition.get_y() >= height_) {
    throw std::out_of_range("Food: Index out of range");
  }
  return (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()] == Food;
}


bool Board::isSnakeBody(const DirectedPosition& kDirectedPosition) const {
  if (kDirectedPosition.get_x() < 0 || kDirectedPosition.get_x() >= width_ || 
      kDirectedPosition.get_y() < 0 || kDirectedPosition.get_y() >= height_) {
    throw std::out_of_range("SnakeBody: Index out of range");
  }
  return (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()] == SnakeBody;
}


bool Board::isSnakeHead(const DirectedPosition& kDirectedPosition) const {
  if (kDirectedPosition.get_x() < 0 || kDirectedPosition.get_x() >= width_ || 
      kDirectedPosition.get_y() < 0 || kDirectedPosition.get_y() >= height_) {
    throw std::out_of_range("SnakeHead: Index out of range");
  }
  return (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()] == SnakeHead;
}


// TODO: Put an enum here
void Board::turnGame(const int& kDirection) {
  moveSnake(kDirection);
  changeSnakeSquare();
}


void Board::moveSnake(const int& kDirection) {
  snake_->move(kDirection);
}


void Board::consumeFood(const int& x, const int& y) {
  (*board_)[x][y] = Empty;
}


void Board::consumeFood(const DirectedPosition& kDirectedPosition) {
  (*board_)[kDirectedPosition.get_y()][kDirectedPosition.get_x()] = Empty;
}


void Board::generateFood() {
  int y = rand() % width_;
  int x = rand() % height_;
  while ((*board_)[x][y] != Empty) {
    y = rand() % width_;
    x = rand() % height_;
  }
  (*board_)[x][y] = Food;
}


void Board::setFood(const int& x, const int& y) {
  (*board_)[x][y] = Food;
};


void Board::gameOver() {
  std::cout << "Game Over" << std::endl;
  exit(0);
}


const Vector<Board::Square>& Board::operator[](const int& kIndex) const {
  if (kIndex < 0 || kIndex >= (*board_).size()) {
    throw std::out_of_range("Row index out of range");
  }
  return (*board_)[kIndex];
}


Vector<Board::Square>& Board::operator[](const int& kIndex) {
  if (kIndex < 0 || kIndex >= (*board_).size()) {
    throw std::out_of_range("Row index out of range");
  }
  return (*board_)[kIndex];
}


std::ostream& operator<<(std::ostream& os, const Board& kBoard) {
  for (int i = -1; i < kBoard.get_height() + 1; i++) {
    for (int j = -1; j < kBoard.get_width() + 1; j++) {
      if (kBoard.isBorder(i, j)) {
          os << "🧱";
      } else {
        if (kBoard.isFood(i, j)) {
          os << "🍎";
        } else if (kBoard.isSnakeHead(i, j)) {
          os << "🟢";
        } else if (kBoard.isSnakeBody(i, j)) {
          os << "🟩";
        } else {
          os << "⬜";
        }
      }
    }
    os << std::endl;
  }
  return os;
}


void Board::changeSnakeSquare() {
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      if ((*board_)[i][j] == SnakeHead || (*board_)[i][j] == SnakeBody) {
        (*board_)[i][j] = Empty;
      }
      if (snake_->isHead(DirectedPosition(i, j))) {
        (*board_)[i][j] = SnakeHead;
      }
      else if (snake_->isBody(DirectedPosition(i, j))) {
        (*board_)[i][j] = SnakeBody;
      }
    }
  }
}


void Board::changeSnakeSquare(const int& x, const int& y) {
  DirectedPosition currentPosition(x, y);
  if (snake_->isHead(currentPosition)) {
    (*board_)[x][y] = SnakeHead;
  }
  else if (snake_->isBody(currentPosition)) {
    (*board_)[x][y] = SnakeBody;
  }
}