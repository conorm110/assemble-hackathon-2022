#include <Servo.h>

#define joystick 0
#define tilt_switch_in 2 
#define buzzer 3
#define status_led 4
#define servo_pin 9

Servo servo_arm;

void setup() {
  Serial.begin(9600);
  
  servo_arm.attach(servo_pin);
  pinMode(tilt_switch_in, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(status_led, OUTPUT);
}


int tilt_switch_interval = 2;
unsigned long previous_tilt_millis = 0;
double shake_size = 0.0;
double shake_decay_rate = 0.5;
double shake_thresh = 5.0;
double shake_max = 30.0;
bool shake_en_last = false;
bool check_if_shaking() {
  unsigned long current_tilt_millis = millis();
  if (current_tilt_millis - previous_tilt_millis >= tilt_switch_interval) {
    // this code should run every 2ms but im bad at timing so im not sure sorry best
    previous_tilt_millis = current_tilt_millis;
    
    if (digitalRead(tilt_switch_in) && shake_size < shake_max) {
      shake_size++;
    }

    if (shake_size > shake_decay_rate) {
      shake_size -= shake_decay_rate;
    }

    if (shake_size > shake_thresh) {
      return true;
    }
  }
  
  return false;
}

unsigned long previous_erase_millis = 0;
const int erase_switch_interval = 700;
bool handle_shaking() {
  unsigned long current_erase_millis = millis();
  bool erase_last_bit = false;
  if (!shake_en_last) {
    shake_en_last = check_if_shaking();
    erase_last_bit = shake_en_last;
  } else if (current_erase_millis - previous_erase_millis >= erase_switch_interval){
    previous_erase_millis = current_erase_millis;
    shake_en_last = false;
  }
  return erase_last_bit;
}

short ascii_buffer_index = 0;
char ascii_buffer[] = "01001000"; // will be overwritten
short joystick_state = 0; // 0 idle, 1 is 0b, 2 is 1b

unsigned long previous_loop_millis = 0;
const long interval_loop = 30;

void loop() {
  unsigned long current_loop_millis = millis();
  if (current_loop_millis-previous_loop_millis>=interval_loop)
  {
    previous_loop_millis = current_loop_millis;
    // Eyeball light lights up when waiting for first bit (MSB) of next ascii code
    if (ascii_buffer_index == 0){
      digitalWrite(status_led, HIGH);
    } else {
      digitalWrite(status_led, LOW);
    }
    
    if(handle_shaking()){
      delay(1); // SORRY BEST IT FIXED IT OK ITS ONLY THIS ONE
      if(ascii_buffer_index > 0) { //
        ascii_buffer_index--;
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
    }
  
    // Code Below handles joystick
    short joystick_new_state = 0;
    int joystick_voltage = analogRead(joystick);
    if(joystick_voltage > 500) {
      joystick_new_state = 2; // 1 in binary
    } else if(joystick_voltage < 200) {
      joystick_new_state = 1;
    } else {
      joystick_new_state = 0;
    }
    if(joystick_new_state != joystick_state) {
      if(joystick_new_state != 0) {
        if(joystick_new_state == 1) {
          ascii_buffer[ascii_buffer_index]= '1';
        } else {
          ascii_buffer[ascii_buffer_index]= '0';
        }
        ascii_buffer_index++;
      }
      joystick_state = joystick_new_state;
    }
  
    if(ascii_buffer_index > 7) {
      char actual_char = 0; 
      for (int bit_pos = 7; bit_pos >= 0; bit_pos--) {
        int the_bit = ascii_buffer[bit_pos] - '0'; // convert from char representation '0', '1' to 0, 1
        actual_char |= the_bit<<(7 - bit_pos); 
      }
      Serial.print(actual_char);
      ascii_buffer_index = 0;
    }
  }
}
