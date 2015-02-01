/*************************************************************
 * Dog Bot Motor Code. Codename: Sparky
 * 
 * @author: Audrey Yeoh
 *************************************************************/

#include "NewPing.h"
#include "GP2D02.h"
#include <Servo.h> 

#define STOP 128
// array size of the 2d "mapping" (doesn't actually map without encoder data)
#define ARRAY_SIZE 20
// 2 ir on the servo, servo steps = array size /2 
#define SERVO_STEPS ARRAY_SIZE/2
// Servo increment: 9 degrees? 
#define SERVO_INC 90/SERVO_STEPS
// each array bracket is 9 degrees diff

Servo ir_servo;
int ir_map[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int forward_error = 5;

int servo_direction = SERVO_INC;
int servo_pos = 0;
int pin_servo = 9;

int pin_motorA = 5;
int pin_motorB = 6;

int forward_thresh = 90;

int front_right_vin = 22;
int front_right_vo = 23;
int front_left_vin = 24;
int front_left_vo = 25;
int left_vin = 26;
int left_vo = 27;
int right_vin = 28;
int right_vo = 29;



/*
const int INPUT_DATA_PIN = 7;
 const int OUTPUT_CLOCK_PIN = 2; // the wire with diode (yellow)
 GP2D02 distanceSensor(INPUT_DATA_PIN,OUTPUT_CLOCK_PIN);*/

// declare IR objects
GP2D02 ir_front_right(front_right_vo, front_right_vin);
GP2D02 ir_front_left(front_left_vo, front_left_vin);
GP2D02 ir_left(left_vo, left_vin);
GP2D02 ir_right(right_vo, right_vin);

void setup(){
  pinMode(pin_motorA, OUTPUT);
  pinMode(pin_motorB, OUTPUT);
  ir_servo.attach(pin_servo);
  Serial.begin(115200);
  brake(1000);
}


void forward(int time, int sp){
  int target_sp = map(sp, 0, 100, 128, 255);
  analogWrite(pin_motorA, target_sp);
  analogWrite(pin_motorB, target_sp);
  delay(time);
}

void backward(int time, int sp){
  int target_sp = map(sp, 0, 100, 127, 0);
  analogWrite(pin_motorA, target_sp);
  analogWrite(pin_motorB, target_sp);
  delay(time);
}

void brake(int time){
  analogWrite(pin_motorA, 128);
  analogWrite(pin_motorB, 128);
  delay(time);
}

void left(int time, int left, int right){
  analogWrite(pin_motorA, left);
  analogWrite(pin_motorB, right);
  delay(time);
}

void right(int time, int left, int right){
  analogWrite(pin_motorA, left);
  analogWrite(pin_motorB, right);
  delay(time);
}

void loop(){

  // moving forward if nothing is in the front (look in the array (middle values)) and if it is not a new array
  if(checkCenterClear() && !newArray()){
    forward(30, 20); // move forward a little
    if(servo_pos + servo_direction > 90){
      servo_direction = -servo_direction;
    }
    // while moving forward, move the servo by an increment
    int servo_target = servo_pos + servo_direction;
    ir_servo.write(servo_target);
    delay(10);
    
    // take measurement 
    ir_front_right.refresh();
    byte dist_front_right = ir_front_right.read();
    ir_front_left.refresh();
    byte dist_front_left = ir_front_left.read();
    
    // update the array tracker
    ir_map[servo_pos/9] = dist_front_left - forward_error;
    ir_map[servo_pos/9+ARRAY_SIZE/2] = dist_front_right - forward_error;
    // update for errors in the past values from moving forward!
    updateError();
    
    // we now know where the object (if there is one is)
    // TODO?: move towards the gradient with lowest value? Or just keep moving forward anyways? 
    // Maybe a pid with confidence towards the values that seem to be further away. 
  }
  // if new array grab measurements first
  // take full array measurement
  // if there is an object in front, turn towards the area with the current lowest gradient in values (in place)
  // shift values in array left or right depending on the movement made. 


  /*
  if(dist_front_right > forward_thresh || dist_front_left > forward_thresh){
   brake(100);
   }
   else{
   forward(100, 30);
   }*/

  /*
  Serial.print(dist_front_right);
   Serial.print("\t");  
   Serial.print(dist_front_left);
   Serial.print("\t");
   Serial.print(dist_left);
   Serial.print("\t");
   Serial.println(dist_right);*/

  /*
  forward(1000, 30);
   brake(2000);
   backward(1000, 30);
   brake(2000);
   left(1000, 150, STOP);
   right(1000, STOP, 150);*/
}

/* If it's a new array, all values should be set to 0
 */
boolean newArray(){
  for(int i = 0; i < ARRAY_SIZE; i ++){
    if (ir_map[i] != 0) return false; 
  }
  return true;
}

/* Checks if the center is clear from obstacles and the robot is
 * alright to move forward. This is done by checking the center few 
 * points on the map to determine whether that part of the path is clear. 
 * Returns a true for a clear path
 */
boolean checkCenterClear(){
  int centerGroup = 6; // number of values to check to certify center is "clear"
  for (int i = ARRAY_SIZE/2; i < (ARRAY_SIZE/2+centerGroup/2); i++){
    if(ir_map[i] > forward_thresh) return false; // that means there is something close
  }

  for (int i = ARRAY_SIZE/2-1; i > (ARRAY_SIZE/2-centerGroup/2-1); i--){
    if(ir_map[i] > forward_thresh) return false;
  }
  return true;
}

/* update for map error from moving forward while taking the measurement. 
 * The update adds a small value to the values already in the map 
 * The current measurement does not have the error and therefore the error is 
 * removed from the measurement before it is added into the ir_map.
 */ 
void updateError(){
  for (int i = 0; i < ARRAY_SIZE; i++){
    ir_map[i] += forward_error;
  }
}






