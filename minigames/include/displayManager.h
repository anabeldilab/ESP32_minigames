/*#include <Arduino.h>
#include "heltec.h"
#include <Wire.h>
#include "oled/SSD1306Wire.h"

class Board;
class DirectedPosition;

class DisplayManager {
 public:
  DisplayManager();
  DisplayManager(SSD1306Wire* display);

  ~DisplayManager();

  void initializeDisplay();

  void drawGameOver(const Board& kBoard);
  void drawScore(const Board& kBoard);
  void drawBorder(const DirectedPosition& kPosition, const Board& kBoard);
  void drawPixel(const DirectedPosition& kPosition);

  void update();



 private:
  // display_ is a pointer to a pointer to a SSD1306Wire object
  SSD1306Wire* display_;
};*/