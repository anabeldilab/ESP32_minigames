typedef enum {
  START,
  RUNNING,
  GAMEOVER
} State;

extern State gameState;

const int screenWidth = 128; // OLED display width, in pixels
const int screenHeight = 64; // OLED display height, in pixels

const int mapSizeX = 40;
const int mapSizeY = 20;


void resetSnake();
void drawMap();
void drawGameover();
void drawScore();
void setupGame();