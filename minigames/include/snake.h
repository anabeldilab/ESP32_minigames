#include <iostream>

class Board;
class Position;

class Snake {
 public:
  Snake();
  Snake(Board* board, Position* position);
  Snake(Board* board);

  ~Snake();

  bool isHead(const Position& kPosition) const;
  bool isBody(const Position& kPosition) const;

  bool CheckFood();
  bool CheckCollision();

  friend std::ostream& operator<<(std::ostream& os, const Snake& kSnake);
  
 private:
  Board* board_;

  int body_size_;
  Position** body_;

  Position* head_position_;
  Position* next_head_position_;

  bool delete_position_;
};