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
  * g++ main.cpp src/board.cpp src/directedPosition.cpp src/snake.cpp -o bin/minigame
  * ./bin/minigame
*/
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>

#include "include/directedPosition.h"
#include "include/snake.h"
#include "include/board.h"


// Function to configure the terminal in non-canonical mode
void enableRawMode() {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw);
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


// Function to check if key press is available
bool keyPressed() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_SET(STDIN_FILENO, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}


int main(int argc, char** argv) {
  enableRawMode();
  Board board(40, 30);
  int direction = 3; // Default direction

  std::cout << board << std::endl;

  while(true) {
    if (keyPressed()) {
      char c;
      read(STDIN_FILENO, &c, 1);
      switch(c) {
        case 'w': direction = 0; break; // Up
        case 's': direction = 1; break; // Down
        case 'a': direction = 2; break; // Left
        case 'd': direction = 3; break; // Right
        case 'q': return 0;            // Quit
        default: break;                // Keep current direction
      }
    }

    board.turnGame(direction);
    std::cout << board << std::endl;
    usleep(100000);
  }
  return 0;
}
