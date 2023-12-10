#include "Arduino.h"
#include "heltec.h"
#include "images.h"

#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64 // OLED display height, in pixels

typedef enum {
  LEFT,
  UP,
  RIGHT,
  DOWN
} Direction;

typedef enum {
  START,
  RUNNING,
  GAMEOVER
} State;

State gameState;

#define SNAKE_PIECE_SIZE     3
#define MAX_SANKE_LENGTH   165
#define MAP_SIZE_X          40
#define MAP_SIZE_Y          20
#define STARTING_SNAKE_SIZE  5

int SNAKE_MOVE_DELAY = 25;

int8_t snake[MAX_SANKE_LENGTH][2];
uint8_t snake_length;
Direction dir;
Direction newDir;

int8_t fruit[2];

// Pines del joystick
const int pinX = 12;
const int pinY = 13;
const int sw = 17;

const int threshold = 1850; // Average value of the analog signal
const int sensitivity = 1000; // Sensitivity to detect movement

volatile bool swPressed = false;

// switchPressed interruption routine in RAM
void IRAM_ATTR switchPressed() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 60 && gameState == START) {
    Serial.println("Switch Pressed");
    swPressed = true;
  }
  last_interrupt_time = interrupt_time;
}


void setup() {
  Serial.begin(115200);
  Serial.println("Ready....");

  Heltec.begin(true, false, true);
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(sw, INPUT_PULLUP);

  // interruption for sw button
  attachInterrupt(digitalPinToInterrupt(sw), switchPressed, FALLING);

  setupGame();
}


void resetSnake() {
  snake_length = STARTING_SNAKE_SIZE;
  for (int i = 0; i < snake_length; i++) {
    snake[i][0] = MAP_SIZE_X / 2 - i;
    snake[i][1] = MAP_SIZE_Y / 2;
  }
}


void setupGame() {
  gameState = START;
  dir = RIGHT;
  newDir = RIGHT;
  resetSnake();
  generateFruit();
  Heltec.display->clear();
  for (int i = 0; i < 5; i++) {
    Serial.println("ecccoci");
    Heltec.display->clear();
    Heltec.display->display();
    delay(100);
    Heltec.display->drawXbm(50, 10, Snake_width, Snake_height, Snake_bits);
    Heltec.display->display();
    delay(200);
  }
  drawMap();
  drawScore();
}


int moveTime = 0;
void loop() {
  switch (gameState) {
    case START:
      Serial.println("START: Press SW to start: ");
      Serial.println(swPressed);
      if (swPressed) {
        gameState = RUNNING;
        swPressed = false;
      }
      break;

    case RUNNING:
      moveTime++;
      readDirection(joystickDirection());
      if (moveTime >= SNAKE_MOVE_DELAY) {
        if (canChangeDirection(dir, newDir)) {
          dir = newDir;
        }
        Heltec.display->clear();

        if (moveSnake()) {
          gameState = GAMEOVER;
          drawGameover();
          delay(1000);
        }
        drawMap();
        drawScore();
        Heltec.display->display();
        checkFruit();
        moveTime = 0;
      }
      break;

    case GAMEOVER:
      if (joystickDirection()) {
        delay(500);
        setupGame();
        gameState = START;
      }
      break;
  }
  delay(10);
}

int joystickDirection() {
  int valorX = analogRead(pinX);
  int valorY = analogRead(pinY);

  if (valorX < threshold - sensitivity) {
    Serial.println("Left");
    return LEFT;
  }
  if (valorX > threshold + sensitivity) {
    Serial.println("Right");
    return RIGHT;
  }
  if (valorY < threshold - sensitivity) {
    Serial.println("Down");
    return DOWN;
  }
  if (valorY > threshold + sensitivity) {
    Serial.println("Up");
    return UP;
  }
  return -1;
}


void readDirection(const int newDirection) {
  if (newDirection >= 0) {
    newDir = (Direction)newDirection;
  }
}


bool canChangeDirection(const Direction& kCurrentDir, const Direction& kNewDir) {
  if ((kCurrentDir == LEFT && kNewDir == RIGHT) ||
    (kCurrentDir == RIGHT && kNewDir == LEFT) ||
    (kCurrentDir == UP && kNewDir == DOWN) ||
    (kCurrentDir == DOWN && kNewDir == UP)) {
    return false;
  }
  return true;
}


bool moveSnake() {
  int8_t x = snake[0][0];
  int8_t y = snake[0][1];

  switch (dir) {
    case LEFT:
      x -= 1;
      break;
    case UP:
      y -= 1;
      break;
    case RIGHT:
      x += 1;
      break;
    case DOWN:
      y += 1;
      break;
  }
  

  if (collisionCheck(x, y)) {
    return true;
  }
  for (int i = snake_length - 1; i > 0; i--) {
    snake[i][0] = snake[i - 1][0];
    snake[i][1] = snake[i - 1][1];
  }

  snake[0][0] = x;
  snake[0][1] = y;
  return false;
}


void checkFruit() {
  if (fruit[0] == snake[0][0] && fruit[1] == snake[0][1]) {
    if (snake_length + 1 <= MAX_SANKE_LENGTH)
      snake_length++;
    generateFruit();
  }
}


void generateFruit() {
  fruit[0] = random(0, MAP_SIZE_X);
  fruit[1] = random(0, MAP_SIZE_Y);
  while (collisionCheck(fruit[0], fruit[1])) {
    fruit[0] = random(0, MAP_SIZE_X);
    fruit[1] = random(0, MAP_SIZE_Y);
  }
}


bool collisionCheck(int8_t x, int8_t y) {
  for (int i = 1; i < snake_length; i++) {
    if (x == snake[i][0] && y == snake[i][1]) return true;
  }
  if (x < 0 || y < 0 || x >= MAP_SIZE_X || y >= MAP_SIZE_Y) return true;
  return false;
}


void drawMap() {
  int offsetMapX = SCREEN_WIDTH - SNAKE_PIECE_SIZE * MAP_SIZE_X - 2;
  int offsetMapY = 2;
  Heltec.display->drawRect(fruit[0] * SNAKE_PIECE_SIZE + offsetMapX, fruit[1] * SNAKE_PIECE_SIZE + offsetMapY, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE);
  Heltec.display->drawRect(offsetMapX - 2, 0, SNAKE_PIECE_SIZE * MAP_SIZE_X + 4, SNAKE_PIECE_SIZE * MAP_SIZE_Y + 4);
  for (int i = 0; i < snake_length; i++) {
    Heltec.display->fillRect(snake[i][0] * SNAKE_PIECE_SIZE + offsetMapX, snake[i][1] * SNAKE_PIECE_SIZE + offsetMapY, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE);
  }
}


void drawGameover() {
  Heltec.display->drawXbm(MAP_SIZE_X / 2 + 5, MAP_SIZE_Y / 2, gameover_width, gameover_height,  gameover_bits);
  Heltec.display->display();
  delay(500);
}


void drawScore() {
  Heltec.display->drawString(0, 0, String(snake_length - STARTING_SNAKE_SIZE));
}
