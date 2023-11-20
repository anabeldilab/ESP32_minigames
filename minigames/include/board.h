#include <iostream>
#include <vector>

class Snake;
class Position;
class Square;

class Board {
 public:
  Board();
  Board(const int& kWidth, const int& kHeight);

  ~Board();

  int get_width(void) const;
  int get_height(void) const;
  Snake* get_snake(void) const;
  Square& get_square(const Position& kPosition);

  bool isBorder(const Position& kPosition) const;

  const std::vector<Square>& operator[](const int& kIndex) const;
  std::vector<Square>& operator[](const int& kIndex);

  friend std::ostream& operator<<(std::ostream& os, const Board& kBoard);

 private:
  int width_;
  int height_;

  std::vector<std::vector<Square>> board_;

  Snake* snake_;
};
