/*
 *  GP2D02.cpp
 *  
 *
 *  Created by Scott Bezek on 6/10/09.
 *
 */

#include "GP2D02.h"
#include "Arduino.h"

GP2D02::GP2D02(int inputDataPin, int outputClockPin){
	_inputDataPin=inputDataPin;
	_outputClockPin=outputClockPin;
	
	pinMode(_outputClockPin, OUTPUT);
	pinMode(_inputDataPin, INPUT);
	digitalWrite(_outputClockPin,HIGH);
}

void GP2D02::refresh(){
	if (millis() < _lastReadMillis + 5){
		return;
	}
	
	byte distanceData = 72; //start with non-zero number to help troubleshoot
	digitalWrite(_outputClockPin,LOW);
	delayMicroseconds(5);
	int safetyCounter=0;
	while(digitalRead(_inputDataPin)!=HIGH && safetyCounter<999)  //wait for input high
	{
		safetyCounter++;
		delayMicroseconds(1000);
	}
	delay(4);
	distanceData=shiftIn();
	
	
	digitalWrite(_outputClockPin,HIGH);
	
	//Serial.println(safetyCounter,DEC);
	
	_distance = distanceData;
	_lastReadMillis = millis();
}

byte GP2D02::read() {
	return _distance;
}


//shiftIn function adopted from http://www.arduino.cc/en/Tutorial/ShftIn22

////// ----------------------------------------shiftIn function
///// just needs the location of the data pin and the clock pin
///// it returns a byte with each bit in the byte corresponding
///// to a pin on the shift register. leftBit 7 = Pin 7 / Bit 0= Pin 0
byte GP2D02::shiftIn() {
	int i;
	int temp = 0;
	int pinState;
	byte myDataIn = 0;
	
	pinMode(_outputClockPin, OUTPUT);
	pinMode(_inputDataPin, INPUT);
	//we will be holding the clock pin high 8 times (0,..,7) at the
	//end of each time through the for loop
	
	//at the begining of each loop when we set the clock low, it will
	//be doing the necessary low to high drop to cause the shift
	//register's DataPin to change state based on the value
	//of the next bit in its serial information flow.
	//The register transmits the information about the pins from pin 7 to pin 0
	//so that is why our function counts down
	
	digitalWrite(_outputClockPin, 1);
	
	for (i=7; i>=0; i--)
	{
		delayMicroseconds(50);
		digitalWrite(_outputClockPin, 0);
		delayMicroseconds(50);
		temp = digitalRead(_inputDataPin);
		if (temp) {
			pinState = 1;
			//set the bit to 0 no matter what
			myDataIn = myDataIn | (1 << i);
		}
		else {
			//turn it off -- only necessary for debuging
			//print statement since myDataIn starts as 0
			pinState = 0;
		}
		
		//Debuging print statements
		//Serial.print(pinState);
		//Serial.print("     ");
		//Serial.println (dataIn, BIN);
		
		digitalWrite(_outputClockPin, 1);
		
	}
	//debuging print statements whitespace
	//Serial.println();
	//Serial.println(myDataIn, BIN);
	return myDataIn;
}
