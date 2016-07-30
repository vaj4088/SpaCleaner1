// Do not remove the include below
#include "SpaCleaner1.h"
//
// Original as modified by IBS Ian Shef 12 July 2016
//
// Major modifications by IBS Ian Shef 30 July 2016 to change from
// operating servos to operating relays.
//

//
// Change these constants to match hardware.
//
const byte panelPin = 9;       // The digital pin used for the relay that
                               // operates the panel on/off button.
const byte filterPumpPin = 10; // The digital pin used for the relay that
                               // operates the filter on/off button.
const byte ledPin = 13 ;       // The pin for the built-in LED.
//
// Useful constants, do not change.
//
const bool WAIT = true ;
const bool DONTWAIT = false ;
const int ON  = HIGH ;
const int OFF =  LOW ;
const int millisPerSecond = 1000 ;
const int secondsPerMinute = 60 ;
const int minutesPerHour = 60 ;
//
//  Change these constants as needed for proper operation
//
const int powerOnDelayMillis = 5000 ; 	// Wait this many milliseconds
										// after power has been applied.
const int buttonOnTime = 500 ; 			// Turn on button or relay for
										// this many milliseconds.
const double filterTimeHours = 2.0 ;	// How long to filter,
										// in decimal hours.
const double filterPeriodHours = 24 ;	// How long from start of filter to
										// next start of filter,
										// in decimal hours.
//
//  Calculated constants
//
const unsigned long filterTimeMillis = filterTimeHours *
		millisPerSecond * secondsPerMinute * minutesPerHour ;
const unsigned long filterPeriodMillis = filterPeriodMillis *
		millisPerSecond * secondsPerMinute * minutesPerHour ;
//
// Object definitions, if any.
//

//
// enum definitions, if any
//
enum State {WAITING_FOR_TURN_ON, WAITING_TO_TURN_OFF} ;

void setup()
{
	pinMode(panelPin,  OUTPUT) ;
	digitalWrite(panelPin, OFF) ;
	pinMode(filterPumpPin, OUTPUT) ;
	digitalWrite(filterPumpPin, OFF) ;
	pinMode(ledPin, OUTPUT) ;
	digitalWrite(ledPin, OFF) ;
	reduceUnusedPinPower() ;
	delay(powerOnDelayMillis) ;
	}
void loop()
{
	unsigned long currentTime = millis() ;
	digitalWrite(ledPin, ON) ;       // Built-in red LED turns on.
	digitalWrite(ledPin, OFF) ;      // Built-in red LED turns off.
}
void reduceUnusedPinPower() {
	//
	// The following reduces power at unused pins.
	//
	for (int i = 2; i<=13; i++) {
		if ((i!=panelPin)&&(i!=filterPumpPin)&&(i!=ledPin)) {
			pinMode(i, INPUT_PULLUP) ;
			digitalWrite(i,OFF) ;
		}
	}
}
