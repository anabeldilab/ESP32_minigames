#include <Arduino.h>

#include "../include/snake.h"
#include "../include/game.h"

int snakeMoveDelay = 25;
int8_t snake[maxSnakeLength][2];
uint8_t snake_length;
Direction dir;
Direction newDir;

int8_t fruit[2];

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
    if (snake_length + 1 <= maxSnakeLength)
      snake_length++;
    generateFruit();
  }
}


void generateFruit() {
  fruit[0] = random(0, mapSizeX);
  fruit[1] = random(0, mapSizeY);
  while (collisionCheck(fruit[0], fruit[1])) {
    fruit[0] = random(0, mapSizeX);
    fruit[1] = random(0, mapSizeY);
  }
}


bool collisionCheck(int8_t x, int8_t y) {
  for (int i = 1; i < snake_length; i++) {
    if (x == snake[i][0] && y == snake[i][1]) return true;
  }
  if (x < 0 || y < 0 || x >= mapSizeX || y >= mapSizeY) return true;
  return false;
}