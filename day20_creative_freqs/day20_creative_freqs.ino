#include <TM1637Display.h>
 
// Rotary Encoder Inputs
#define CLK2 2
#define DT2 4
#define SW2 3
 
// Define the display connection pins:
#define CLK 6
#define DIO 5
 
// Create display object of type TM1637Display:
TM1637Display OurDisplay = TM1637Display(CLK, DIO);
  
// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
 
int counter = 0;    // keep a running tally of steps...
int currentStateCLK;
int lastStateCLK;
int buzzer = 10;  // pin 10 drives the buzzer
int toneFreq = 0;

int lastButton;
 
void setup() {
 
  // Set encoder pins as inputs
  pinMode(CLK2,INPUT);
  pinMode(DT2,INPUT);
  pinMode(SW2, INPUT_PULLUP);
 
  // Setup Serial Monitor
  Serial.begin(9600);
 
  // Read the initial state of A (CLK)
  lastStateCLK = digitalRead(CLK2);
  lastButton = digitalRead(SW2);
 
  // Clear the display:
  OurDisplay.clear();
  OurDisplay.setBrightness(7);
 
  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (CLK2) interrupt  (pin 2), or B (DT2) interrupt (pin 3)
 
  attachInterrupt(digitalPinToInterrupt(CLK2), updateEncoder, CHANGE);
}
 
void loop() {
  OurDisplay.showNumberDec(counter);
  if (digitalRead(SW2) == LOW) {
    tone(buzzer, counter * 10);
  } else {
    noTone(buzzer);
  }
  
  delay(50); 
  
}
 
//  This is our ISR which has the job of responding to interrupt events
//
void updateEncoder(){
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK2);
 
  // If last and current state of CLK are different, then a pulse occurred;
  // React to only 0->1 state change to avoid double counting
  if (currentStateCLK != lastStateCLK){
 
    // If the DT state is different than the CLK state then
    // the encoder is rotating CW so INCREASE counter by 1
    if (digitalRead(DT2) != currentStateCLK) {
      counter ++;
    } else {
      // Encoder is rotating CCW so DECREASE counter by 1
      counter --;
    }
  }
 
  // Remember last CLK state to use on next interrupt...
  lastStateCLK = currentStateCLK;
}
