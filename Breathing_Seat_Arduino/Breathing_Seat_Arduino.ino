/*
 * 
 * JMIR '17 paper in-car movements part 2
 * Author: Nur Hamdan
 * Date: Non. 19, 2016
 * 
 * Edited by Maddy Bernstein
 * Date: 24 Aug 2018
 */

#include "BreathingHS.h"
#include "HapticSeat.h"
#include "ExercisesHS.h"

// A0, A1 are pre-defined as analaog inputs for first row and col.
// Note A5,A6 are INACTIVE.
#define BUTT1_PIN A2
#define BUTT2_PIN A3
#define BUTT3_PIN A4
#define BUTT4_PIN A5
#define BUTT5_PIN A6

// 2-dimensional array of row pin numbers:
const byte colPins[7] = {2, 3, 4, 5, 6, 7, A1};
// 2-dimensional array of column pin numbers:
const byte rowPins[7] = {8, 9, 10, 11, 12, 13, A0};

void setup() {
  Serial.begin(9600);
  
  // Setup input pins
  pinMode(BUTT1_PIN, INPUT_PULLUP);
  pinMode(BUTT2_PIN, INPUT_PULLUP);
  pinMode(BUTT3_PIN, INPUT_PULLUP);
  pinMode(BUTT4_PIN, INPUT_PULLUP);

  // Setup output pins
  resetPins();
}

/*
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * THIS IS WHERE YOU WILL ASSIGN ACTIONS TO BUTTONS.
 * THERE ARE 8 VIBRATIONS, BUT ONLY 4 BUTTONS.
 * RUN ONLY THE FIRST 4 IF STATEMENTS FIRST.
 * (COMMENT OUT THE SECOND 4).
 * THEN COMMENT OUT THE FIRST 4 AND RUN THE SECOND 4.
 * BUTTON 1 CORRESPONDS TO THE BUTTON ON THE VERY SIDE OF THE REMOTE.
 */

int bpm = 6; //breaths per min. - original default: 7
int holdDuration = 100; // hold between breaths - original default: 100
int height = 1; //2 short, 1 medium, 0 tall - maybe could eventually be set/selected by a button
int wait_time = 1; // wait time before starting haptics in minutes
int min_diration = 10;  // time that haptics will be on in minutes

int state = 0;
int start_time = 0;
int breathDuration = (60000 - ((bpm*2)*holdDuration))/(bpm*2);
    
void loop() {
  int time = 200;

  if (digitalRead(BUTT1_PIN) == LOW) { // when green button is pushed:
    state = 100; // run code state
    start_time = millis();
  }

  if ((millis() - start_time) > wait_time*60000 && state == 100) {  // wait_time before turning actuators on
    state = 200; // enter haptic state
  }

  if (state == 200) { // swipe up/swipe down breathing exercise   
    for (int i = 0; i < bpm*min_diration; i++){
        breathInStrokeUp_Height(breathDuration, height);    
        delay(holdDuration);
        breathOutStrokeDown_Height(breathDuration, height);
        delay(holdDuration);
     }
     state = 0;       
   }
 
}

