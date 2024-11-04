  #include "led_mat.h"
  
  void LedMatrixController::init() {
    matrix.begin();
    clear();
  }
  void LedMatrixController::clear() {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 12; j++) {
        frame[i][j] = 0;
      }
    }
  }
  uint8_t* LedMatrixController::getFrame() {
    uint8_t* p = &frame[0][0];
    return p;
  }
  void LedMatrixController::render() {
    matrix.renderBitmap(frame, 8, 12);
  }
  void LedMatrixController::drawPoint(uint8_t r, uint8_t c) {
    clear();
    frame[r][c] = 1;
    render();
  }
  void LedMatrixController::drawChar(char c[], bool scroll) {
    matrix.beginDraw();
    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(SCROLL_SPEED);
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(c);
    if (scroll)
      matrix.endText(SCROLL_LEFT);
    else 
      matrix.endText();
    matrix.endDraw();
  }
  void LedMatrixController::drawChar(char c[]) {
    drawChar(c, false);
  }
