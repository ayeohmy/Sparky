/* Motors.h - Library to control motors on Sparky
 * @Author: Audrey Yeoh (ayeoh)
 * @modified: 2/11/2015
 */

#ifndef Motors_h
#define Motors_h

#include "Arduino.h"

class Motors
{
	public:
		Motors(int pin_motorA, int pin_motorB);
		void forward(int time, int speed);
		void backward(int time, int speed);
		void brake(int time);
		void left(int time, int left, int right);
		void right(int time, int left, int right);
	private: 		 
		int _pin_motorA;
		int _pin_motorB;
};

#endif