// Do not remove the include below
#include "SpaCleaner1.h"
#include <VarSpeedServo.h>
//
// Original as modified by IBS Ian Shef 12 July 2016
//

//
// Change these constants to match hardware.
//
const byte panelPin = 9;       // The digital pin used for the servo that
                               // operates the panel on/off button.
const byte filterPumpPin = 10; // The digital pin used for the servo that
                               // operates the filter on/off button.
const byte ledPin = 13 ;       // The pin for the built-in LED.
//
// Useful constants, do not change.
//
const bool WAIT = true ;
const bool DONTWAIT = false ;
const int ON  = HIGH ;
const int OFF =  LOW ;
//
// Object definitions.
//
VarSpeedServo panel ;       // Create a servo object to control the panel servo.
VarSpeedServo filterPump ;  // Create a servo object to control the
void setup()
{
	  panel.attach(panelPin) ;        // Attaches the panel servo pin
	                                  // to the panel servo object.
	  panel.write(0,255,DONTWAIT) ;   // Sets the initial position of
	                                  // the panel servo,
	                                  // as fast as possible, run in background
	  filterPump.attach(filterPumpPin) ; // Attaches the filter pump servo pin
	                                     // to the filter pump servo object.
	  filterPump.write(0,255,WAIT) ;     // Sets the initial position of the
	                                     // filter pump servo,
	                                     // as fast as possible,
	                                     // wait until done.
}
void loop()
{
	//
    // .write(degrees 0-180, speed 1-255, wait to complete true-false)
	//
	  panel.write(180,255,DONTWAIT) ;  // Move the panel servo to 180 degrees,
	                                   // fast speed, run in background.
	  filterPump.write(0,255,WAIT) ;   // Move the filter pump servo
	                                   // to 0 degrees,
	                                   // fast speed, wait until done.
	  digitalWrite(ledPin, ON) ;       // Built-in red LED turns on.
	  panel.write(0,30,DONTWAIT) ;     // Move the panel servo to 0 degrees,
	                                   // slow speed, run in background.
	  filterPump.write(180,30,WAIT) ;  // Move the filter pump servo
	                                   // to 180 degrees,
	                                   // slow speed, wait until done.
	  digitalWrite(ledPin, OFF) ;      // Built-in red LED turns off.
}
