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

int bpm = 6; // breaths per min. - original default: 7
int holdDuration = 100; // original default: 100
int height = 1; //2 short, 1 medium, 0 tall - maybe could eventually be set/selected by a button

int breathDuration = (60000 - ((bpm*2)*holdDuration))/(bpm*2);
    
void loop() {
  int time = 200;

  /*
   * THIS CODE WILL ALLOW FOR AN ON/OFF BUTTON EFFECT WITH THE GREEN BUTTON.
   * HOWEVER BUTTON MUST BE HELD DOWN TILL STOP.
   */
  if (digitalRead(BUTT1_PIN) == LOW) //funcitons based off of button pulling input pin LOW
  {
    while(true) {
      //testBreathing(breathDuration);
      
      breathInStrokeUp_Height(breathDuration, height);    
      //breathInStrokeUp(breathDuration);
      delay(holdDuration);
      breathOutStrokeDown_Height(breathDuration, height);
      //breathOutStrokeDown(breathDuration);
      delay(holdDuration);
      
      if(digitalRead(BUTT1_PIN) == LOW) {
        break;
      }
    }
  }

/*
  if (digitalRead(BUTT1_PIN) == LOW) { 
    for (int i = 0; i < bpm; i++)
    {
      //breathInSpiral(breathDuration);
      //delay(holdDuration); //hold
      //breathOutSpiral();
      //delay(holdDuration); //hold
      
      breathInStrokeUp_Height(breathDuration, height);    
      //breathInStrokeUp(breathDuration);
      delay(holdDuration);
      breathOutStrokeDown_Height(breathDuration, height);
      //breathOutStrokeDown(breathDuration);
      delay(holdDuration);
      
      //breathSpotN(breathDuration, 5); 
      //delay(holdDuration);
      //breathSpotN(breathDuration, 6);
        
    }
  }
*/

/*
  if (digitalRead(BUTT2_PIN) == LOW) {
    for (int i = 0; i < bpm; i++)
      {
        breathInFlower(breathDuration);
        delay(holdDuration); //hold
        breathOutFlower(breathDuration);
        delay(holdDuration); //hold
      }
  }

  if (digitalRead(BUTT3_PIN) == LOW) {
    //Multi lines, 2 directions up/down, gradual
    for (int i = 0; i < bpm; i++)
    {
      breathInSwipUp(breathDuration);
      delay(holdDuration); //hold
      breathOutSwipDown(breathDuration);
      delay(holdDuration); //hold
    }

  }

  if (digitalRead(BUTT4_PIN) == LOW) {
    //Multi lines, 2 directions left/right, gradual
    for (int i = 0; i < bpm; i++)
    {
      breathInAccordion(breathDuration);
      delay(holdDuration); //hold
      breathOutAccordion(breathDuration);
      delay(holdDuration); //hold
    }
    
   }
*/     
}

