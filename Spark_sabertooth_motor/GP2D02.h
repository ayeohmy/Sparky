/*
 *  GP2D02.h
 *  
 *
 *  Created by Scott Bezek on 6/10/09.
 *
 */

#ifndef GP2D02_h
#define GP2D02_h

#include "Arduino.h"

class GP2D02
	{
	public:
		GP2D02(int inputDataPin, int outputClockPin);
		void refresh();
		byte read();
	private:
		int _inputDataPin;
		int _outputClockPin;
		byte _distance;
		unsigned long _lastReadMillis;
		byte shiftIn();
	};

#endif
