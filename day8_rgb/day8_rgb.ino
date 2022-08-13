int red = 11;
int green = 10;
int blue = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void RGB_color(int red_value, int green_value, int blue_value) {
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
}

void loop() {
  // put your main code here, to run repeatedly:
  RGB_color(125, 0, 0); // Red
  delay(800);
  RGB_color(0, 125, 0); // Green
  delay(800);
  RGB_color(0, 0, 125); // Blue
  delay(800);
  RGB_color(64, 32, 0); // yellow
  delay(800);
  RGB_color(125, 0, 125); // purple
  delay(800);
  RGB_color(125, 125, 125); // white
  delay(2000);
}
