enum Direction {Up, Down, Left, Right};

class DirectedPosition {
 public:
  DirectedPosition();
  DirectedPosition(const int& y, const int& x);
  DirectedPosition(const int& y, const int& x, const Direction& direction);
  
  int get_x(void) const;
  int get_y(void) const;
  Direction get_direction(void) const;

  void set_x(const int&);
  void set_y(const int&);

  void turnRight(const Direction& kDirection);
  void turnLeft(const Direction& kDirection);
  void turnDirection(const Direction& kDirection);

  DirectedPosition nextPosition() const;

  bool operator==(const DirectedPosition&);
  bool operator!=(const DirectedPosition&);
  DirectedPosition operator+(const DirectedPosition&);

  bool operator==(const DirectedPosition&) const;
  bool operator!=(const DirectedPosition&) const;
  DirectedPosition operator+(const DirectedPosition&) const;

  friend std::ostream& operator<<(std::ostream& os, const DirectedPosition& kDirectedPosition);

 private:
  Direction direction_;
  int x_;
  int y_;
};