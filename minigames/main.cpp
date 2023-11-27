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
  * g++ main.cpp src/board.cpp src/display.cpp src/directedPosition.cpp src/snake.cpp src/square.cpp -o bin/minigame
  * ./bin/minigame
*/

#include "include/display.h"
#include "include/directedPosition.h"
#include "include/snake.h"
#include "include/square.h"
#include "include/board.h"

int main(int argc, char** argv) {
  Board board(5, 10);

  std::cout << board << std::endl;

  while(true) {
    //Up, Down, Left, Right
    std::cout << "Snake Size: " << board.get_snake()->get_body_size() << std::endl;
    std::cout << "Direction: Up = 0, Down = 1, Left = 2, Right = 3" << std::endl;
    std::cout << "Enter a direction: ";
    int direction;
    std::cin >> direction;
    board.turnGame(direction);
    std::cout << board << std::endl;
  }

  return 0;
}
