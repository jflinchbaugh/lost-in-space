int sensorPin = A0;
int onboardLED = 13;
int sensorValue = 0;
unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;
double percentFull;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(onboardLED, OUTPUT);
}

void printBatteryPercentage() {
// print the elasped time
  Serial.print(ticks);
  Serial.print(" ms    charge at ");
 
//  convert the integers to decimal numbers, divide them and print...
  percentFull=100*((double)batteryLevel / (double)batteryCapacity);
  Serial.print(percentFull);
 
// print a percent character and line return...
  Serial.println("%");
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
    delay(20000);      // long pause
  }
  else {
    printBatteryPercentage();
  }
 
  delay(wait);
}
