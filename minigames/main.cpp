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
  * g++ main.cpp src/board.cpp src/display.cpp src/position.cpp src/snake.cpp src/square.cpp -o bin/minigame
  * ./bin/minigame
*/

#include "include/display.h"
#include "include/position.h"
#include "include/snake.h"
#include "include/square.h"
#include "include/board.h"

int main(int argc, char** argv) {
  Board board(10, 10);

  std::cout << board << std::endl;

  return 0;
}
