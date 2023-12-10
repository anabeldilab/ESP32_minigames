class Snake;
class DirectedPosition;
class DisplayManager;
template <typename T> class Vector;

class Board {
 public:
  enum Square {Empty, Food, SnakeBody, SnakeHead};

  Board();
  Board(const int& kHeight, const int& kWeight);

  ~Board();

  int get_width(void) const;
  int get_height(void) const;
  Snake *get_snake(void) const;
  Square get_square(const int& x, const int& y) const;
  Square get_square(const DirectedPosition& kDirectedPosition) const;

  bool isBorder(const int& x, const int& y) const;
  bool isFood(const int& x, const int& y) const;
  bool isSnakeBody(const int& x, const int& y) const;
  bool isSnakeHead(const int& x, const int& y) const;

  bool isBorder(const DirectedPosition& kDirectedPosition) const;
  bool isFood(const DirectedPosition& kDirectedPosition) const;
  bool isSnakeBody(const DirectedPosition& kDirectedPosition) const;
  bool isSnakeHead(const DirectedPosition& kDirectedPosition) const;

  void turnGame(const int& kDirection);

  void moveSnake(const int& kDirection);
  void generateFood();
  void setFood(const int& x, const int& y);
  void consumeFood(const int& x, const int& y);
  void consumeFood(const DirectedPosition& kDirectedPosition);
  void gameOver();

  const Vector<Square> &operator[](const int &kIndex) const;
  Vector<Square> &operator[](const int &kIndex);

  friend std::ostream &operator<<(std::ostream &os, const Board &kBoard);
  void displayBoard(DisplayManager& manager);
  
 private:
  int width_;
  int height_;

  Vector<Vector<Square>>* board_;

  Snake *snake_;

  void changeSnakeSquare();
  void changeSnakeSquare(const int& x, const int& y);
};
