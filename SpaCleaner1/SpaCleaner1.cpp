// Do not remove the include below
#include "SpaCleaner1.h"
//
// Original as modified by IBS Ian Shef 12 July 2016
//
// Major modifications by IBS Ian Shef 30 July 2016 to change from
// operating servos to operating relays.

// Completed modifications and commit message
// IBS Ian Shef 9 August 2016
// to change from operating servos to operating relays.
//

// From Nick Gammon in Australia on 31 July 2016
// from URL http://www.gammon.com.au/millis
/*
 * Recommended method for performing timing

> Use unsigned long (not just long) for "time" variables.
> Record the start time of some event
  (eg. a debounce, when you start feeding the fish, etc.)
> Subtract the start time from the time now, giving a difference.
> See if the difference exceeds the desired interval.

eg.

startedFeedingFish = millis ();
...
if (millis () - startedFeedingFish >= 20000)  // feed them for 20 seconds
  {
  // stop feeding the fish
  }

 */

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
const unsigned long powerOnDelayMillis = 5000 ; // Wait this many
												// milliseconds
												// after power has been applied.
const unsigned long buttonOnTime = 500 ; 		// Turn on button or relay for
												// this many milliseconds.
const unsigned long buttonToButtonTime = 3000 ;	// Wait between buttons for
												// this many milliseconds.
const double filterTimeHours = 2.0 ;	// How long to filter,
										// in decimal hours.
const double filterPeriodHours = 24 ;	// How long from start of filter to
										// next start of filter,
										// in decimal hours.
//
//  Calculated constants
//
#define TEST 1
#ifdef TEST
	const unsigned long filterTimeMillis = 4 * millisPerSecond ;
	const unsigned long filterPeriodMillis = 10 * millisPerSecond ;
#else
	const unsigned long filterTimeMillis = filterTimeHours *
			millisPerSecond * secondsPerMinute * minutesPerHour ;
	const unsigned long filterPeriodMillis = filterPeriodHours *
			millisPerSecond * secondsPerMinute * minutesPerHour ;
#endif
//
// Object definitions, if any.
//

//
// enum definitions, if any
//
enum State {RESET,
	WAIT_TO_PRESS_PANEL_BUTTON,
	WAIT_TO_RELEASE_PANEL_BUTTON,
	WAIT_TO_PRESS_FILTER_BUTTON,
	WAIT_TO_RELEASE_FILTER_BUTTON,
	WAIT_TO_PRESS_PANELBUTTON2,
	WAIT_TO_RELEASE_PANEL_BUTTON2
} ;

//
// Global variables
//
State state = RESET ;
unsigned long lastActionTime ;	// The processor time (in milliseconds)
								// when the last significant action was taken,
								// which is the same as when the state changes.
unsigned long lastFilterTime ;	// The processor time (in milliseconds)
								// when the last filtering started.

void setup()
{
	pinMode(panelPin,  OUTPUT) ;
	digitalWrite(panelPin, OFF) ;
	pinMode(filterPumpPin, OUTPUT) ;
	digitalWrite(filterPumpPin, OFF) ;
	pinMode(ledPin, OUTPUT) ;
	digitalWrite(ledPin, OFF) ;
	reduceUnusedPinPower() ;
	lastActionTime = millis() ;
	}
void loop()
{
	const unsigned long currentTime = millis() ;
	switch (state) {
	case RESET:
		if (currentTime-lastActionTime>=powerOnDelayMillis) {
			turnLedOn() ;
			lastFilterTime = currentTime ;
			pressPanelButton() ;
			newState(WAIT_TO_RELEASE_PANEL_BUTTON) ;
		}
		break ;
	case WAIT_TO_PRESS_PANEL_BUTTON:
		if (currentTime-lastFilterTime>=filterPeriodMillis) {
			turnLedOn() ;
			lastFilterTime = currentTime ;
			pressPanelButton() ;
			newState(WAIT_TO_RELEASE_PANEL_BUTTON) ;
		}
		break ;
	case WAIT_TO_RELEASE_PANEL_BUTTON:
		if (currentTime-lastActionTime>=buttonOnTime) {
			releasePanelButton() ;
			newState(WAIT_TO_PRESS_FILTER_BUTTON) ;
		}
		break ;
	case WAIT_TO_PRESS_FILTER_BUTTON:
		if (currentTime-lastActionTime>=buttonToButtonTime) {
			pressFilterButton() ;
			newState(WAIT_TO_RELEASE_FILTER_BUTTON) ;
		}
		break ;
	case WAIT_TO_RELEASE_FILTER_BUTTON:
		if (currentTime-lastActionTime>=buttonOnTime) {
			releaseFilterButton() ;
			newState(WAIT_TO_PRESS_PANELBUTTON2) ;
		}
		break ;
	case WAIT_TO_PRESS_PANELBUTTON2:
		if (currentTime-lastActionTime>=filterTimeMillis) {
			pressPanelButton() ;
			newState(WAIT_TO_RELEASE_PANEL_BUTTON2) ;
		}
		break ;
	case WAIT_TO_RELEASE_PANEL_BUTTON2:
		if (currentTime-lastActionTime>=buttonOnTime) {
			releasePanelButton() ;
			newState(WAIT_TO_PRESS_PANEL_BUTTON) ;
			turnLedOff() ;
		}
		break ;
	default:
		newState(RESET) ;
		break ;  // Unnecessary but makes Eclipse compiler happy.
	}
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
void pressPanelButton() {
	digitalWrite(panelPin, ON) ;
}
void releasePanelButton() {
	digitalWrite(panelPin, OFF) ;
}
void pressFilterButton() {
	digitalWrite(filterPumpPin, ON) ;
}
void releaseFilterButton() {
	digitalWrite(filterPumpPin, OFF) ;
}
void turnLedOn() {
	digitalWrite(ledPin, ON) ;       // Built-in red LED turns on.
}
void turnLedOff() {
	digitalWrite(ledPin, OFF) ;       // Built-in red LED turns off.
}
void newState(State x) {
	state = x ;
	lastActionTime=millis() ;
}

