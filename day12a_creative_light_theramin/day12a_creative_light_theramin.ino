// change this to whichever pin you want to use
int buzzer = 10;
int photoDiode = A0;
  
void setup() {
}
 
void loop() {
  int freq = ((analogRead(photoDiode) - 40) * 4) / 110 * 110;

  tone(buzzer, freq);
}
