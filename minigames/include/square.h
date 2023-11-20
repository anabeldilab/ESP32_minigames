#include <iostream>

class Position;

class Square {
 public:
  Square();
  Square(Position* position);

  ~Square();

  bool isFood() const;
  bool isSnakeBody() const;
  bool isSnakeHead() const;

  void setFood(const bool& kNewFood);
  void setSnakeHead(const bool& kNewSnakeHead);
  void setSnakeBody(const bool& kNewSnakeBody);

  friend std::ostream& operator<<(std::ostream& os, const Square& kSquare);

 private:
  Position* position_;
  bool food_;
  bool snake_body_;
  bool snake_head_;

  bool delete_position_;
};