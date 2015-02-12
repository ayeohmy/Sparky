/*************************************************************
 * Dog Bot Motor Code. Codename: Sparky
 * 
 * @author: Audrey Yeoh
 *************************************************************/
// to do: get encoder values to make 2d map

#include "NewPing.h"
#include "GP2D02.h"
#include <Servo.h> 
#include "Motors.h"

#define STOP 128

Servo ir_servo;

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
//GP2D02 ir_left(left_vo, left_vin);
//GP2D02 ir_right(right_vo, right_vin);
Motors motor(pin_motorA, pin_motorB);

void setup(){
  //pinMode(pin_motorA, OUTPUT);
  //pinMode(pin_motorB, OUTPUT);
  ir_servo.attach(pin_servo);
  Serial.begin(115200);
  motor.brake(1000);
}

void loop(){

  ir_front_right.refresh();
  byte dist_front_right = ir_front_right.read();
  ir_front_left.refresh();
  byte dist_front_left = ir_front_left.read();
  
  // moving forward if nothing is in the front (look in the array (middle values))
  // while move the servo by an increment
    // take measurement 
    // update the array tracker
  
  
/*
  if(dist_front_right > forward_thresh || dist_front_left > forward_thresh){
    brake(100);
  }
  else{
    forward(100, 30);
  }*/


  Serial.print(dist_front_right);
  Serial.print("\t");  
  Serial.println(dist_front_left);

  
   motor.forward(1000, 30);
   motor.brake(2000);
   motor.backward(1000, 30);
   motor.brake(2000);
   motor.left(1000, 150, STOP);
   motor.right(1000, STOP, 150);
}






