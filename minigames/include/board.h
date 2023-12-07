class Snake;
class DirectedPosition;
class Square;
template <typename T> class Vector;
//class DisplayManager;

class Board {
 public:
  Board();
  Board(const int& kHeight, const int& kWeight);

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

  const Vector<Square> &operator[](const int &kIndex) const;
  Vector<Square> &operator[](const int &kIndex);

  friend std::ostream &operator<<(std::ostream &os, const Board &kBoard);
  //friend void displayBoard(DisplayManager& manager, const Board& board);
  
 private:
  int width_;
  int height_;

  Vector<Vector<Square>>* board_;

  Snake *snake_;

  void changeSnakeSquare();
  void changeSnakeSquare(const DirectedPosition& kDirectedPosition);
  void clean();
};
