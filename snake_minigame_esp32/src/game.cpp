#include <Arduino.h>
#include <heltec.h>

#include "../include/game.h"
#include "../include/snake.h"
#include "../include/images.h"

State gameState;

void drawMap() {
  int offsetMapX = screenWidth - snakePieceSize * mapSizeX - 2;
  int offsetMapY = 2;
  Heltec.display->drawRect(fruit[0] * snakePieceSize + offsetMapX, fruit[1] * snakePieceSize + offsetMapY, snakePieceSize, snakePieceSize);
  Heltec.display->drawRect(offsetMapX - 2, 0, snakePieceSize * mapSizeX + 4, snakePieceSize * mapSizeY + 4);
  for (int i = 0; i < snake_length; i++) {
    Heltec.display->fillRect(snake[i][0] * snakePieceSize + offsetMapX, snake[i][1] * snakePieceSize + offsetMapY, snakePieceSize, snakePieceSize);
  }
}


void drawGameover() {
  Heltec.display->drawXbm(mapSizeX / 2 + 5, mapSizeY / 2, gameover_width, gameover_height,  gameover_bits);
  Heltec.display->display();
  delay(500);
}


void drawScore() {
  Heltec.display->drawString(0, 0, String(snake_length - startingSnakeSize));
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


void resetSnake() {
  snake_length = startingSnakeSize;
  for (int i = 0; i < snake_length; i++) {
    snake[i][0] = mapSizeX / 2 - i;
    snake[i][1] = mapSizeY / 2;
  }
}
