// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef SpaCleaner1_H_
#define SpaCleaner1_H_
#include "Arduino.h"
//add your includes for the project SpaCleaner1 here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

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

//add your function definitions for the project SpaCleaner1 here
void reduceUnusedPinPower() ;
void pressPanelButton() ;
void releasePanelButton() ;
void pressFilterButton() ;
void releaseFilterButton() ;
void turnLedOn() ;
void turnLedOff() ;
void newState(State x) ;


//Do not add code below this line
#endif /* SpaCleaner1_H_ */
