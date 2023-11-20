class Position {
 public:
  Position();
  Position(int x, int y);
  
  int get_x(void) const;
  int get_y(void) const;

  void set_x(const int&);
  void set_y(const int&);

  bool operator==(const Position&);
  bool operator!=(const Position&);
  Position operator+(const Position&);

 private:
  int x_;
  int y_;
};