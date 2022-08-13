int sensorPin = A0;
int sensorValue = 0;

int red = 11;
int green = 10;
int blue = 9;


void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  Serial.begin(9600);
}

void RGB_color(int red_value, int green_value, int blue_value) {
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
}

void loop() {
  sensorValue = analogRead(sensorPin); // read the value from the sensor:
  double percent = (double) (sensorValue - 17) / 690 * 100;

  Serial.print(sensorValue);
  Serial.print(", ");
  Serial.print(percent);
  Serial.println("%");

  if (sensorValue < 50) {
    RGB_color(255,255,255);
  } else if (sensorValue < 200) {
    RGB_color(100,100,100);
  } else if (sensorValue < 500) {
    RGB_color(25,25,25);
  } else {
    RGB_color(0,0,0);
  }

  delay(200);
}
