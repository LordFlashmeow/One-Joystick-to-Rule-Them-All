#include <Servo.h>

int x_joy_pin = A0;
int y_joy_pin = A1;
int z_joy_pin = A2;

int x_joy_value;
int y_joy_value;
int z_joy_value;

int fl_thruster_pin = 3;
int fr_thruster_pin = 5;
int bl_thruster_pin = 6;
int br_thruster_pin = 9;

Servo fl_thruster_servo;
Servo fr_thruster_servo;
Servo bl_thruster_servo;
Servo br_thruster_servo;

int fl_thruster_value;
int fr_thruster_value;
int bl_thruster_value;
int br_thruster_value;
int turn_value;


void setup() {
  
  Serial.begin(9600);
  
  pinMode(x_joy_pin, INPUT);
  pinMode(y_joy_pin, INPUT);
  pinMode(z_joy_pin, INPUT);
  
  
  fl_thruster_servo.attach(fl_thruster_pin);
  fr_thruster_servo.attach(fr_thruster_pin);
  bl_thruster_servo.attach(bl_thruster_pin);
  br_thruster_servo.attach(br_thruster_pin);
  
  fl_thruster_servo.writeMicroseconds(1500);
  fr_thruster_servo.writeMicroseconds(1500);
  bl_thruster_servo.writeMicroseconds(1500);
  br_thruster_servo.writeMicroseconds(1500);
  
  delay(7000);
}

void loop() {
  x_joy_value = analogRead(x_joy_pin);
  y_joy_value = analogRead(y_joy_pin);
  z_joy_value = analogRead(z_joy_pin);
  

  // Serial.print(" ");
  // Serial.println(z_joy_value);
  
  
  fl_thruster_value = map(x_joy_value, 0, 1023, 1100, 1900);
  fr_thruster_value = map(y_joy_value, 0, 1023, 1100, 1900);
  bl_thruster_value = map(x_joy_value, 0, 1023, 1900, 1100);  // Reverse map for rear thrusters
  br_thruster_value = map(y_joy_value, 0, 1023, 1900, 1100);  // Reverse map for rear thrusters
    // 
  
  
  if (z_joy_value < 100) {
    turn_value = map(z_joy_value, 0, 80, -400, 0);
  }
  else if (z_joy_value > 110) {
    turn_value = map(z_joy_value, 85, 640, 0, 400);
  }
  else {
    turn_value = 0;
  }
  
  // Add turn values
  fl_thruster_value += turn_value;
  fr_thruster_value -= turn_value;
  bl_thruster_value -= turn_value;
  br_thruster_value += turn_value;
  
  if (fl_thruster_value > 1900) {fl_thruster_value = 1900;}
  if (fr_thruster_value > 1900) {fr_thruster_value = 1900;}
  if (bl_thruster_value > 1900) {bl_thruster_value = 1900;}
  if (br_thruster_value > 1900) {br_thruster_value = 1900;}
  
  if (fl_thruster_value < 1100) {fl_thruster_value = 1100;}
  if (fr_thruster_value < 1100) {fr_thruster_value = 1100;}
  if (bl_thruster_value < 1100) {bl_thruster_value = 1100;}
  if (br_thruster_value < 1100) {br_thruster_value = 1100;}
  
  Serial.print(x_joy_value);
  Serial.print(" ");
  Serial.print(y_joy_value);
  Serial.print(" ");
  Serial.print(z_joy_value);
  Serial.print(" ");
  Serial.print(fl_thruster_value);
  Serial.print(" ");
  Serial.print(fr_thruster_value);
  Serial.print(" ");
  Serial.print(bl_thruster_value);
  Serial.print(" ");
  Serial.print(br_thruster_value);
  Serial.print(" ");
  Serial.println(turn_value);
  
  
  fl_thruster_servo.writeMicroseconds(fl_thruster_value);
  fr_thruster_servo.writeMicroseconds(fr_thruster_value);
  bl_thruster_servo.writeMicroseconds(bl_thruster_value);
  br_thruster_servo.writeMicroseconds(br_thruster_value);
  
  delay(250);
}
