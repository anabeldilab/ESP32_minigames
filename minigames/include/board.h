#include <iostream>
#include <vector>

class Snake;
class DirectedPosition;
class Square;

class Board {
 public:
  Board();
  Board(const int& kWidth, const int& kHeight);

  ~Board();

  int get_width(void) const;
  int get_height(void) const;
  Snake *get_snake(void) const;
  Square &get_square(const DirectedPosition& kDirectedPosition); // TODO this is for ardino testing

  bool isBorder(const DirectedPosition& kDirectedPosition) const;

  void turnGame(const int& kDirection);

  void moveSnake(const int& kDirection);
  void generateFood();
  void consumeFood(const DirectedPosition& kDirectedPosition);
  void gameOver();

  const std::vector<Square> &operator[](const int &kIndex) const;
  std::vector<Square> &operator[](const int &kIndex);

  friend std::ostream &operator<<(std::ostream &os, const Board &kBoard);

private:
  int width_;
  int height_;

  std::vector<std::vector<Square>> board_;

  Snake *snake_;

  // TODO: revision
  void changeSnakeSquare();
  void changeSnakeSquare(const DirectedPosition& kDirectedPosition);
  void clean();
};
