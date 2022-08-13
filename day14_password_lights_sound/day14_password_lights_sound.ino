#include <Key.h>
#include <Keypad.h>

int buzzer = 8;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
 
const byte ROWS = 4;
const byte COLS = 4;
const byte PassLength = 4;  // passwords will be 4 characters long
char currentPassword[PassLength] = {'0','0','0','0'}; // default before setting
 
char buttons[ROWS][COLS] = {
  {'1', '2', '3', 'A'},  // 1st row
  {'4', '5', '6', 'B'},  // 2nd row
  {'7', '8', '9', 'C'},  // 3rd row
  {'*', '0', '#', 'D'}   // 4th row
};
 
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 12, 13};
 
Keypad securityPad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);
 
 
//  custom function to process a login attempt *******************************
 
int unlockMode(){
    char result ;

    RGB_color(0,0,0);
    
    Serial.println("Unlock Mode: Type Password to continue");
    delay(500);
   
    for(int i = 0; i < PassLength; i++) {
       while(!(result = securityPad.getKey())) {
         // wait indefinitely for keypad input of any kind
       }
       if(currentPassword[i] != result){     // a wrong key was pressed
          Serial.println("WRONG PASSWORD");
          Serial.println(result);
          playError();
          return -1;                    //  -1 means failed -- return immediately
       }
       Serial.print("*");  // print a phantom character for a successful keystroke
       playInput();
       RGB_color(0,0,125);
       delay(100);
       RGB_color(0,0,0);
    }  //  done after 4 characters are accepted
   
    Serial.println("");
    Serial.println("Device Successfully Unlocked!");
    playSuccess();
    return 0;           //  0 means succeeded
}
//  ************************************************************************

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  RGB_color(125,125,125);
  delay(200);
  RGB_color(0,0,0);
  
  Serial.begin(9600); // Begin monitoring via the serial monitor
  delay(2000);
  Serial.println("Press * to set a new password.");
  Serial.println("Press # to access the system with the existing one.");
}
 
void loop() {
  char result = securityPad.getKey();
 
 
   if (result == '*'){           // choice to change password
    int access = unlockMode();
   
    if(access < 0) {
      Serial.println("Access Denied. Cannot change password without knowing the previous or default.");
      RGB_color(125,0,0);
    }
    else {
      RGB_color(0,125,0);
      delay(2000);
      RGB_color(0,0,0);
      Serial.println("Welcome, authorized user. Please Enter a new password: ");
      delay(500);
   
      for(int i = 0; i < PassLength; i++) {
        while(!(result = securityPad.getKey())) {
        // wait indefinitely for keypad input of any kind
        }
   
        currentPassword[i] = result;
        Serial.print("*");    // print a phantom character for a successful keystroke
        playInput();
        RGB_color(0,0,125);
        delay(100);
        RGB_color(0,0,0);
      }   //  done after 4 characters are accepted
     
      Serial.println("");
      Serial.println("Password Successfully Changed!");
      RGB_color(0,125,0);
    }
  }
 
  else if (result == '#') {           // choice to access system with current password
    int access = unlockMode();
    if(access < 0) {
      Serial.println("Password error. Access Denied.");
      RGB_color(125,0,0);
    }
    else {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
      RGB_color(0,125,0);
    }
  }
 
}

void RGB_color(int red_value, int green_value, int blue_value) {
  analogWrite(redPin, red_value);
  analogWrite(greenPin, green_value);
  analogWrite(bluePin, blue_value);
}

//  custom functions to give audio feedback *******************************
 
void playSuccess() {
  tone(buzzer, 1000, 200);
  delay(200);
  tone(buzzer, 2700, 1000);
  delay(1000);
  noTone(buzzer);
}
 
void playError() {
  tone(buzzer, 147, 200);
  delay(100);
  noTone(buzzer);
}
 
void playInput() {
  tone(buzzer, 880, 200);
  delay(50);
  noTone(buzzer);
}
