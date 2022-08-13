int light = 12;

void setup() {
  // put your setup code here, to run once:

  pinMode(light, OUTPUT);
  digitalWrite(light, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(light, LOW);
  delay(1000);
  digitalWrite(light, HIGH);
  delay(100);
}
