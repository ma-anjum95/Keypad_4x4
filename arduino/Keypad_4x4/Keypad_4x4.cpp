/*******************************************************************************************************	
* 	File Name: Keypad_4x4.cpp
*	Project Name: Keypad_4x4 (Arduino)
* 	
* 	The MIT License (MIT)
*
*	Copyright (c) 2015 M.A. Anjum
*	Email : ma.anjum95@gmail.com
*	
*	Permission is hereby granted, free of charge, to any person obtaining a copy of this software
*	and associated documentation files (the "Software"), to deal in the Software without restriction,
*	including without limitation the rights to use, copy, modify, merge, publish, distribute,
*	sublicense, and/or sell copies of the Software, and to permit persons to whom the Software 
*	is furnished to do so, subject to the following conditions:
*
*	The above copyright notice and this permission notice shall be included in all copies 
*	or substantial portions of the Software.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
*	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
*	AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
*	DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
*	OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
********************************************************************************************************/

#include "Keypad_4x4.h"

Keypad_4x4::Keypad_4x4(byte *pins) {
	for (int i = 0; i < PINS; i++)
		this->pins[i] = pins[i];

	// pins 0-3 should be pulled down by 1k resistor and they are to be made the output
	pinMode(this->pins[0], OUTPUT);
	pinMode(this->pins[1], OUTPUT);
	pinMode(this->pins[2], OUTPUT);
	pinMode(this->pins[3], OUTPUT);

	// initializing the output to be HIGH 1
	digitalWrite(this->pins[0], HIGH);
	digitalWrite(this->pins[1], HIGH);
	digitalWrite(this->pins[2], HIGH);
	digitalWrite(this->pins[3], HIGH);

	// pins 4-7 should be the input and will determine the output of the keypad
	pinMode(this->pins[4], INPUT);
	pinMode(this->pins[5], INPUT);
	pinMode(this->pins[6], INPUT);
	pinMode(this->pins[7], INPUT);

	digitalWrite(this->pins[4], HIGH);
	digitalWrite(this->pins[5], HIGH);
	digitalWrite(this->pins[6], HIGH);
	digitalWrite(this->pins[7], HIGH);
}

char Keypad_4x4::readInput(void) {
	// we loop over the output port 0-3 and set them to HIGH 1 one-by-one
	for (int i = 0; i < 4; i++) {
		digitalWrite(this->pins[i], LOW);
		
		// now we check which input pin is high from pins 4-7
		for (int j = 4; j < 8; j++) {
			// if the current pin is high then the corresponding button is on
			if (!digitalRead(this->pins[j])) {
				digitalWrite(this->pins[i], HIGH); // output should be cleared after each loop
				return returnButtonOutput((7 - j) * 10 + (3 - i));
			}
		}
		digitalWrite(this->pins[i], HIGH); // output should be cleared after each loop
	}

	// if no button is pressed we return -1.
	return -1;
}

char Keypad_4x4::waitForInput(int ms) {
	char toReturn = -1;
	int startTime = millis();

	do {
		toReturn = this->readInput();

		if (toReturn != -1)
			return toReturn;
	
	} while((!ms) || millis() - startTime <= ms);

	return toReturn;
}

char Keypad_4x4::readSingleInput(void) {
	char toReturn = this->readInput();

	// if there is no input we return
	if (toReturn == -1)
		return -1;

	// else we wait till there is an input change ie key is released
	while(this->readInput() == toReturn)
		;

	return toReturn;
}

char Keypad_4x4::waitAndReadSingleInput(int ms) {
	char toReturn = -1;
	int startTime = millis();

	do {
		toReturn = this->readSingleInput();

		if (toReturn != -1)
			return toReturn;

	} while((!ms) || millis() - startTime <= ms);
	
	return toReturn;
}

char Keypad_4x4::returnButtonOutput(int mxn) {
	switch (mxn) {
		case 00:
			return BUTTON_OUTPUT_00;
		case 01:
			return BUTTON_OUTPUT_01;
		case 02:
			return BUTTON_OUTPUT_02;
		case 03:
			return BUTTON_OUTPUT_03;
		case 10:
			return BUTTON_OUTPUT_10;
		case 11:
			return BUTTON_OUTPUT_11;
		case 12:
			return BUTTON_OUTPUT_12;
		case 13:
			return BUTTON_OUTPUT_13;
		case 20:
			return BUTTON_OUTPUT_20;
		case 21:
			return BUTTON_OUTPUT_21;
		case 22:
			return BUTTON_OUTPUT_22;
		case 23:
			return BUTTON_OUTPUT_23;
		case 30:
			return BUTTON_OUTPUT_30;
		case 31:
			return BUTTON_OUTPUT_31;
		case 32:
			return BUTTON_OUTPUT_32;
		case 33:
			return BUTTON_OUTPUT_33;
		default:
			return -1;
	}
}




