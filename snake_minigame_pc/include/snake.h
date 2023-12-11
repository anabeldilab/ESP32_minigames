class Board;
class DirectedPosition;
template <typename T> class Vector;

class Snake {
 public:
  Snake(Board* board, DirectedPosition* position);
  Snake(Board* board);

  ~Snake();

  bool get_body_size(void) const;

  bool isHead(const DirectedPosition& kPosition) const;
  bool isBody(const DirectedPosition& kPosition) const;

  bool checkFood() const;
  bool checkCollision() const;

  void move(const int& direction);
  
 private:
  Board* board_;

  int body_size_;
  Vector<DirectedPosition>* body_;

  DirectedPosition* head_directed_position_;

  bool delete_position_;

  void grow();
  void changeDirection(const int& direction);
  bool oppositeDirection(const int& direction);
  void moveBody();
  void moveHead();
};