#include "../include/board.h"
#include "../include/snake.h"
#include "../include/directedPosition.h"
#include "../include/square.h"

Board::Board() : width_(0), height_(0), 
  board_(std::vector<std::vector<Square>>()), snake_(new Snake(this)) {} // TODO check if this is correct


Board::Board(const int& kHeight, const int& kWidth) 
  : width_(kWidth), height_(kHeight), 
  board_(std::vector<std::vector<Square>>(kHeight, std::vector<Square>(kWidth))), 
  snake_(new Snake(this)) {
  for (int i = 0; i < kHeight; i++) {
    for (int j = 0; j < kWidth; j++) {
      board_[i][j] = Square(new DirectedPosition(i, j));
      changeSnakeSquare(DirectedPosition(i, j));
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


Square& Board::get_square(const DirectedPosition& kDirectedPosition) {
  return board_[kDirectedPosition.get_y()][kDirectedPosition.get_x()];
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


// TODO finish this
void Board::moveSnake(const int& kDirection) {
  snake_->Move(kDirection);
}


void Board::generateFood() {
  int y = rand() % height_;
  int x = rand() % width_;
  while (board_[y][x].isSnakeBody()) {
    y = rand() % height_;
    x = rand() % width_;
  }
  board_[y][x].setFood(true);
}


// TODO finish this
void Board::gameOver() {
  std::cout << "Game Over" << std::endl;
  exit(0);
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


void Board::changeSnakeSquare() {
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      board_[i][j].setSnakeHead(false);
      board_[i][j].setSnakeBody(false);
      if (snake_->isHead(DirectedPosition(i, j))) {
        board_[i][j].setSnakeHead(true);
        board_[i][j].setSnakeBody(true);
      }
      else if (snake_->isBody(DirectedPosition(i, j))) {
        board_[i][j].setSnakeBody(true);
      }
    }
  }
}


void Board::clean() {
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      board_[i][j].setSnakeHead(false);
      board_[i][j].setSnakeBody(false);
    }
  }
}


void Board::changeSnakeSquare(const DirectedPosition& kDirectedPosition) {
  if (snake_->isHead(kDirectedPosition)) {
    board_[kDirectedPosition.get_y()][kDirectedPosition.get_x()].setSnakeHead(true);
    board_[kDirectedPosition.get_y()][kDirectedPosition.get_x()].setSnakeBody(true);
  }
  else if (snake_->isBody(kDirectedPosition)) {
    board_[kDirectedPosition.get_y()][kDirectedPosition.get_x()].setSnakeBody(true);
  }
}