#include "Arduino.h"
#include "heltec.h"

#include "include/game.h"
#include "include/snake.h"

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


void loop() {
  static int moveTime = 0;
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
      if (moveTime >= snakeMoveDelay) {
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