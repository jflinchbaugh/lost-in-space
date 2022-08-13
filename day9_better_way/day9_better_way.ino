int sensorPin = A0;
int sensorValue = 0;

int red = 11;
int green = 10;
int blue = 9;

unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;
double percentFull;

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

double getBatteryPercentage() {
  return 100 * ((double) batteryLevel / (double) batteryCapacity);
}

void showBatteryPercentage() {
  percentFull = getBatteryPercentage();

  // print the elasped time
  Serial.print(ticks);
  Serial.print(" ms    charge at ");
 
//  convert the integers to decimal numbers, divide them and print...
  percentFull=100*((double)batteryLevel / (double)batteryCapacity);
  Serial.print(percentFull);
 
// print a percent character and line return...
  Serial.println("%");

  if (percentFull > 0 && percentFull <= 25)
  {
    RGB_color(125, 0, 0); // red
  }
  else if (percentFull > 25 && percentFull <= 50){
    RGB_color(125, 80, 0); // yellow-ish
  }
  else if (percentFull > 50 && percentFull <= 75) {
    RGB_color(0, 125, 125); // blue-ish
  }
  else if (percentFull > 75 && percentFull < 100) {
    RGB_color(125, 125, 125); // white
  }
}

void loop() {
  sensorValue = analogRead(sensorPin); // read the value from the sensor:
  batteryLevel += sensorValue;
  ticks += wait;
 
  if(batteryLevel >= batteryCapacity) {
    Serial.print(ticks);
    Serial.print(" ms     ");
    Serial.println("FULLY CHARGED");
    batteryLevel = batteryCapacity; // to prevent integer from continuing to increase
    ticks = 0;
    RGB_color(0, 125, 0); // green
    delay(30000);      // long pause
  }
  else {
    showBatteryPercentage();
  }
}
