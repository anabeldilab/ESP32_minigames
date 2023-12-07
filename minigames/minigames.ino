/** Universidad de La Laguna
  * Escuela de Doctorado y Estudios de Postgrado
  * Máster Universitario en Informática Industrial y Robótica
  * Lenguajes de Alto Nivel para Aplicaciones Industriales
  *
  * @author Anabel Díaz Labrador <alu0101206011@ull.edu.es>
  * @date 20 Nov 2023
  * @brief This code contains the implementation of different minigames, such as snake
  * 
  * 
  *
*/

#include "Arduino.h"
#include "heltec.h"

#include "include/displayManager.h"
#include "include/directedPosition.h"
#include "include/snake.h"
#include "include/square.h"
#include "include/board.h"

void drawBorder(int x, int y) {
  if (x == 0 || y == 0 || y == DISPLAY_HEIGHT - 1 || x == DISPLAY_WIDTH - 1 ||
      x == 1 || y == 1 || y == DISPLAY_HEIGHT - 2 || x == DISPLAY_WIDTH - 2) {
    if ((x + y) % 2 == 0) {
      Heltec.display->setPixel(x, y);
    }
  }
}

Board board(30, 30);
DisplayManager displayManager(Heltec.display);

void setup() {
  Serial.begin(115200);
	Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->clear();
  Heltec.display->display();
}

void loop() {
  displayBoard(displayManager, board);
  //displayManager.drawPixel(DirectedPosition(2, 2));
  //Square(DirectedPosition(2, 2)); // this is the error
  //DirectedPosition kPosition(2, 2);
  //Heltec.display->setPixel(2, 2);
  //Heltec.display->display();
  delay(200);
}