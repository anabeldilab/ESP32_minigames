#include <iostream>
#include <vector>

class Board;
class DirectedPosition;

class Snake {
 public:
  Snake();
  Snake(Board* board, DirectedPosition* position);
  Snake(Board* board);

  ~Snake();

  // TODO: Delete
  bool get_body_size(void) const;

  bool isHead(const DirectedPosition& kPosition) const;
  bool isBody(const DirectedPosition& kPosition) const;

  bool CheckFood() const;
  bool CheckCollision() const;

  void Move(const int& direction);
  
 private:
  Board* board_;

  int body_size_;
  std::vector<DirectedPosition> body_;

  DirectedPosition* head_directed_position_;

  bool delete_position_;

  void Grow();
  void ChangeDirection(const int& direction);
  void MoveBody();
};