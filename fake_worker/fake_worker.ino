#include "USB.h"
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"

USBHIDMouse Mouse;
USBHIDKeyboard Keyboard;

void blink(uint8_t duration, uint8_t R, uint8_t G, uint8_t B) {
  /* duration:miliseconds | R:0-255 | G:0-255 | B:0-255 | */
  neopixelWrite(RGB_BUILTIN, R, G, B);
  delay(duration);
  neopixelWrite(RGB_BUILTIN, 0, 0, 0);
}

void moveMouseTo(int dx, int dy) {
  neopixelWrite(RGB_BUILTIN, 32, 0, 32);
  while (dx != 0 || dy != 0) {
    int ddx = dx * (int)random(2, 16) / 100;
    int ddy = dy * (int)random(2, 16) / 100;
    if (ddx == 0 && dx !=0 ) ddx = (dx > 0)?1:-1;
    if (ddy == 0 && dy !=0 ) ddy = (dy > 0)?1:-1;
    ddx = constrain(ddx, -127, 127);
    ddy = constrain(ddy, -127, 127);
    Mouse.move(ddx, ddy);
    dx -= ddx;
    dy -= ddy;
    delay(random(25, 50));
  }
  neopixelWrite(RGB_BUILTIN, 0, 100, 0);
  delay(500);
  neopixelWrite(RGB_BUILTIN, 0, 0, 0);
}

void tapKey(uint8_t key) {
  Keyboard.press(key);
  delay(random(20, 90));
  Keyboard.release(key);
}

void type_rubish_and_delete() {
  int typed = 0;
  int target = random(4, 16);
  while (typed < target) {
    if (random(0, 10) == 0) delay(random(300, 900));
    char c = (random(0, 6) == 0)?' ':(char)('a' + random(0, 26));
    tapKey(c);
    typed++;
  }
  delay(2000);
  while (typed != 0) {
    tapKey(KEY_BACKSPACE);
    typed--;
  }
}

void setup() {
  Mouse.begin();
  Keyboard.begin();
  USB.begin();
  randomSeed(esp_random());
  for (int i=0; i<10; i++){
    blink(50, 32, 0, 0);
    delay(250);
  }
  blink(500, 0, 255, 0);
}

void loop() {
  delay(random(3000, 7000));
  int dx = random(-250, 250);
  int dy = random(-250, 250);
  moveMouseTo(dx, dy);
  delay(random(2000, 4000));
  moveMouseTo(-dx, -dy);
  if (random(0, 3) == 0) type_rubish_and_delete();
}
