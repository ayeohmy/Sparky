/* Motors.cpp - Library for Sparky's Motors (Source)
 * @Author: Audrey Yeoh (ayeoh)
 * @modified: 2/11/2015
 * 
 * This code controls 2 pittman dc motors (19.7:1) with a 
 * sabertooth 2x5 motor controller. It requires a analog 
 * signal in to control the motors. (RC circuit required)
 */

#include "Arduino.h"
#include "Motors.h"

Motors::Motors(int pin_motorA, int pin_motorB)
{
	pinMode(pin_motorA, OUTPUT);
	_pin_motorA = pin_motorA;
	pinMode(pin_motorB, OUTPUT);
	_pin_motorB = pin_motorB;
}

void Motors::forward(int time, int sp)
{
	int target_sp = map(sp, 0, 100, 128, 255);
  	analogWrite(_pin_motorA, target_sp);
  	analogWrite(_pin_motorB, target_sp);
  	delay(time);
}

void Motors::backward(int time, int sp)
{
	int target_sp = map(sp, 0, 100, 127, 0);
  	analogWrite(_pin_motorA, target_sp);
  	analogWrite(_pin_motorB, target_sp);
  	delay(time);
}

void Motors::brake(int time)
{
    analogWrite(_pin_motorA, 128);
    analogWrite(_pin_motorB, 128);
    delay(time);
}

void Motors::left(int time, int left, int right)
{
	analogWrite(_pin_motorA, left);
    analogWrite(_pin_motorB, right);
    delay(time);
}

void Motors::right(int time, int left, int right)
{
  analogWrite(_pin_motorA, left);
  analogWrite(_pin_motorB, right);
  delay(time);	
}

