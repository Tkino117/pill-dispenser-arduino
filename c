[1mdiff --git a/led_mat.cpp b/led_mat.cpp[m
[1mdeleted file mode 100644[m
[1mindex e69de29..0000000[m
[1mdiff --git a/led_mat.h b/led_mat.h[m
[1mdeleted file mode 100644[m
[1mindex 6b554ab..0000000[m
[1m--- a/led_mat.h[m
[1m+++ /dev/null[m
[36m@@ -1 +0,0 @@[m
[31m-#include [m
\ No newline at end of file[m
[1mdiff --git a/main.ino b/main.ino[m
[1mdeleted file mode 100644[m
[1mindex 4a3af7e..0000000[m
[1m--- a/main.ino[m
[1m+++ /dev/null[m
[36m@@ -1,71 +0,0 @@[m
[31m-#include "Arduino_LED_Matrix.h"[m
[31m-[m
[31m-ArduinoLEDMatrix matrix;[m
[31m-[m
[31m-void setup() {[m
[31m-  // Serial.begin(115200);[m
[31m-  matrix.begin();[m
[31m-}[m
[31m-[m
[31m-uint8_t frame[8][12] = {[m
[31m-  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },[m
[31m-  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },[m
[31m-  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },[m
[31m-  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },[m
[31m-  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },[m
[31m-  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },[m
[31m-  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },[m
[31m-  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }[m
[31m-};[m
[31m-[m
[31m-void leftEye(){[m
[31m-  //Left eye[m
[31m-  frame[1][3] = 1;[m
[31m-  frame[1][4] = 1;[m
[31m-  frame[2][3] = 1;[m
[31m-  frame[2][4] = 1;[m
[31m-}[m
[31m-[m
[31m-void wink(){[m
[31m-  //Wink with the left eye[m
[31m-  frame[1][3] = 0;[m
[31m-  frame[1][4] = 0;[m
[31m-  frame[2][3] = 1;[m
[31m-  frame[2][4] = 1;[m
[31m-}[m
[31m-[m
[31m-void rightEye(){[m
[31m-  //Right eye[m
[31m-  frame[1][8] = 1;[m
[31m-  frame[1][9] = 1;[m
[31m-  frame[2][8] = 1;[m
[31m-  frame[2][9] = 1;[m
[31m-}[m
[31m-[m
[31m-void mouth(){[m
[31m-  //Mouth[m
[31m-  frame[5][3] = 1;[m
[31m-  frame[5][9] = 1;[m
[31m-  frame[6][3] = 1;[m
[31m-  frame[6][4] = 1;[m
[31m-  frame[6][5] = 1;[m
[31m-  frame[6][6] = 1;[m
[31m-  frame[6][7] = 1;[m
[31m-  frame[6][8] = 1;[m
[31m-  frame[6][9] = 1;[m
[31m-  frame[4][3] = 1;[m
[31m-}[m
[31m-[m
[31m-void loop(){[m
[31m-  leftEye();[m
[31m-  rightEye();[m
[31m-  mouth();[m
[31m-[m
[31m-  matrix.renderBitmap(frame, 8, 12);[m
[31m-[m
[31m-  delay(1000);[m
[31m-  wink();[m
[31m-[m
[31m-  matrix.renderBitmap(frame, 8, 12);[m
[31m-  delay(1000);[m
[31m-}[m
\ No newline at end of file[m
