#define joystick 0
#define tiltSwIn 2 
#define buzzer 3
#define status_led 4

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
     
bool tiltState = false;

int cycleTotal = 0;
double cycleTilt = 0;

int pos = 0;

int shakeCooldown = 0;

short joystickState = 0; // 0 idle, 1 is 0b, 2 is 1b, 
char on = '1';
char off = '0';

int bufferIndex = 0;
char bufferKeys[] = "01001000"; // will be rewritten

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  pinMode(tiltSwIn, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(status_led, OUTPUT);
}
 
 void loop() {
  if (bufferIndex == 0)
  {
    digitalWrite(status_led, HIGH);
  }
  else
  {
    digitalWrite(status_led, LOW);
  }
  if(shakeCooldown > 0){
    shakeCooldown--;
  }
  
  bool eraseLastBit = false;
  bool newTiltState = digitalRead(tiltSwIn);
  
  if(newTiltState != tiltState) {
    cycleTilt++;
    delay(3.5);
  }
  
  cycleTotal++;
  tiltState = newTiltState; // questionable
  
  if(cycleTotal > 10000) {
    // no shak
    cycleTilt = 0;
    cycleTotal = 0;
  } else if(cycleTilt > 6 && shakeCooldown == 0) {
    eraseLastBit = true;
    shakeCooldown = 1;
    cycleTilt = 0;
    cycleTotal = 0;
  }

  if (cycleTilt > 0.1){
    cycleTilt = cycleTilt - 0.01;
  }


  if(eraseLastBit) {
    if(bufferIndex > 0) { //
      bufferIndex--; // tocuh grass 
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    } else {
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }
  } else {
    short newState = 0;
    int joystickVoltage = analogRead(joystick);
    if(joystickVoltage > 700) {
      newState = 2; // 1 in binary
    } else if(joystickVoltage < 200) {
      newState = 1;
    } else {
      newState = 0;
    }
    
    if(newState != joystickState) {
      if(newState != 0) {
        // write new thing to buffer
        //bufferKeys[bufferIndex] = newState - 1; // TIS IS SO FUCKEd
        if(newState == 1) {
          bufferKeys[bufferIndex]= on;
        } else {
          bufferKeys[bufferIndex]= off;
        }
        //bufferKeys += newState - 1;
        bufferIndex++;
      }
      joystickState = newState;
    }
   
    if(bufferIndex > 7) {
      char actual_char = 0; 
      for (int bit_pos = 7; bit_pos >= 0; bit_pos--) // start from rightmost position 
      {
        int the_bit = bufferKeys[bit_pos] - '0'; // convert from char representation '0', '1' to 0, 1
        actual_char |= the_bit<<(7 - bit_pos); 
      }

      Serial.print(actual_char);

      for (int i = 0; i < 3; i++){
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(1);
      }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(1);
      }}
  
 
      bufferIndex = 0;
    }
  }
}
