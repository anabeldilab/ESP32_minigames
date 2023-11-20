/** Universidad de La Laguna
  * Escuela de Doctorado y Estudios de Postgrado
  * Máster Universitario en Informática Industrial y Robótica
  * Lenguajes de Alto Nivel para Aplicaciones Industriales
  *
  * @author Anabel Díaz Labrador <alu0101206011@ull.edu.es>
  * @date 20 Nov 2023
  * @brief This code contains the implementation of different minigames, such as snake or tetris. 
  *       The user can choose which game to play. 
  * 
  *
*/

#include "heltec.h"
#include "include/display.h"
#include "include/position.h"
#include "include/snake.h"
#include "include/square.h"
#include "include/board.h"

Board board(10, 10);

Snake snake(&board, new Position(5, 5));

void setup() {
  Serial.begin(9600);
  //std::cout << board << std::endl;
  Serial.println("Hola1");
}

void loop() {
  Serial.println("Hola");

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      Serial.print(board.get_square(Position(i,j)).isBorder()); 
    }
    Serial.println();
  } 
  delay(2000);
}