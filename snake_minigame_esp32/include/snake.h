typedef enum {
  LEFT,
  UP,
  RIGHT,
  DOWN
} Direction;

// Pines del joystick
const int pinX = 12;
const int pinY = 13;
const int sw = 17;

const int threshold = 1850; // Average value of the analog signal
const int sensitivity = 1000; // Sensitivity to detect movement

const int snakePieceSize = 3;
const int maxSnakeLength = 165;
const int startingSnakeSize = 5;

extern int snakeMoveDelay;
extern int8_t snake[maxSnakeLength][2];
extern uint8_t snake_length;
extern Direction dir;
extern Direction newDir;

extern int8_t fruit[2];

int joystickDirection();
void readDirection(const int newDirection);
bool canChangeDirection(const Direction& kCurrentDir, const Direction& kNewDir);
bool moveSnake();
void checkFruit();
void generateFruit();
bool collisionCheck(int8_t x, int8_t y);