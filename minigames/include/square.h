#include <iostream>

class DirectedPosition;

class Square {
 public:
  Square();
  Square(DirectedPosition* position);

  ~Square();

  bool isFood() const;
  bool isSnakeBody() const;
  bool isSnakeHead() const;

  void setFood(const bool& kNewFood);
  void setSnakeHead(const bool& kNewSnakeHead);
  void setSnakeBody(const bool& kNewSnakeBody);

  friend std::ostream& operator<<(std::ostream& os, const Square& kSquare);

 private:
  DirectedPosition* directed_position_;
  bool food_;
  bool snake_body_;
  bool snake_head_;

  bool delete_position_;
};