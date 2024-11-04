#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

// How to use
// 1. include "led_mat.h"
// 2. declare LedMatrixController lmc as global variable
// 3. write lmc.init() in setup()
// 4. using draw... methods are recommended

class LedMatrixController {
private:
  ArduinoLEDMatrix matrix;
  uint8_t frame[8][12];
  const uint8_t SCROLL_SPEED = 70;
public:
  void init();
  void clear();
  uint8_t* getFrame();
  void render();
  void drawPoint(uint8_t r, uint8_t c);
  void drawChar(char c[], bool scroll);
  void drawChar(char c[]);
};
