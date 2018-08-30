/*
 * Author: Maddy Bernstein
 * Date: Jul 30, 2018
 * 
 * Referenced Breathing_Seat_Arduino code by Nur Hamdan
 */
 
#include "Arduino.h"
#include "HapticSeat.h"

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

int state;

void setup() {
  Serial.begin(9600);

  // Setup input pins
  pinMode(BUTT1_PIN, INPUT_PULLUP);
  pinMode(BUTT2_PIN, INPUT_PULLUP);
  pinMode(BUTT3_PIN, INPUT_PULLUP);
  pinMode(BUTT4_PIN, INPUT_PULLUP);

  // Setup output pins
  resetPins();
  
  state = 0;  // state = 0 means actuators are all off
}

void loop() {
  if (state == 0) { // Off state
    resetPins();
  } else if (state == 100) {  // On state   
    for (int i = 0; i < 7; i ++) {
      pckge_rowOn(i);
    }
  }
  
  if (digitalRead(BUTT1_PIN) == LOW) {  // On button (marked green)
    state = 100;
  }
  
  if (digitalRead(BUTT4_PIN) == LOW) {  // Off button (marked red)
    state = 0;
  }
}
