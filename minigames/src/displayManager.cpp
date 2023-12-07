/*#include "../include/displayManager.h"
#include "../include/board.h"
#include "../include/directedPosition.h"

DisplayManager::DisplayManager() : display_(nullptr) {}

DisplayManager::DisplayManager(SSD1306Wire* display) : display_(display) {}


DisplayManager::~DisplayManager() {
  delete display_;
}


void DisplayManager::initializeDisplay() {
  display_->clear();
  update();
}


void DisplayManager::drawGameOver(const Board& kBoard) {
  update();
}


void DisplayManager::drawScore(const Board& kBoard) {
  display_->clear();
  update();
}


void DisplayManager::drawBorder(const DirectedPosition& kPosition, const Board& kBoard) {
  if (kPosition.get_x() == 0 || 
      kPosition.get_y() == 0 || 
      kPosition.get_y() == kBoard.get_height() + 1 || 
      kPosition.get_x() == kBoard.get_width() + 1||
      kPosition.get_x() == 1 || 
      kPosition.get_y() == 1 || 
      kPosition.get_y() == kBoard.get_height() || 
      kPosition.get_x() == kBoard.get_width()) {
    if ((kPosition.get_x() + kPosition.get_y()) % 2 == 0) {
      display_->setPixel(kPosition.get_x(), kPosition.get_y());
    }
  }
  update();
}


void DisplayManager::drawPixel(const DirectedPosition& kPosition) {
  display_->setPixel(kPosition.get_x(), kPosition.get_y());
  update();
}


void DisplayManager::update() {
  display_->display();
}
*/