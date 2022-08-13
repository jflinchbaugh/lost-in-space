int led = 12;
int switch1 = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(switch1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(switch1) == HIGH) {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
    
  } else {
    digitalWrite(led, LOW);
  }
}
