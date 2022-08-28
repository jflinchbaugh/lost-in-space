#include "U8glib.h"
 
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C / TWI
long randomEightBall = 0;
 
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
 
  switch (randomEightBall) {
      case 0:
        u8g.drawStr( 0, 22, "Yes");
        break;
      case 1:
        u8g.drawStr( 0, 22, "No");
        break;
      case 2:
        u8g.drawStr( 0, 22, "I'm not sure");
        break;
      case 3:
        u8g.drawStr( 0, 22, "Maybe");
        break;
      case 4:
        u8g.drawStr( 0, 22, "likely");
        break;
      case 5:
        u8g.drawStr( 0, 22, "unlikely");
        break;
      case 6:
        u8g.drawStr( 0, 22, "try again");
        break;
      case 7:
        u8g.drawStr( 0, 22, "Buy More Inventr");
        break;
    }
    delay(50);
}
 
void setup(void) {
  Serial.begin(9600);
  // assign default color value
  u8g.setColorIndex(1); // pixel on
  int seed = analogRead(0);
  Serial.println(seed);
  randomSeed(random(seed));
  delay(30);
  randomEightBall = random(8);
}
 
void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    draw();
  } while( u8g.nextPage() );
 
}
