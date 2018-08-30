
/*
 * These are the methods reperesenting vibration patterns.
 * Method names are self-explanatory.
 * Author:
 * Date:
 */


#include "Arduino.h"
#include "HapticSeat.h"
#include "ExercisesHS.h"

// 2-dimensional array of row pin numbers:
const byte colPins[7] = {2, 3, 4, 5, 6, 7, A1};
// 2-dimensional array of column pin numbers:
const byte rowPins[7] = {8, 9, 10, 11, 12, 13, A0};

 
void sideStretch() {
  fastSwipeOneCol(2,100,50);
  delay(600);
  fastSwipeOneCol(4,100,50);
}

void backTwist() {
  region(1, 2, 1, 2); //LEFT region
  delay(500); //Pause
  region(1, 2, 4, 5); //RIGHT region
}

void bendForwardBackward() {
  fastSwipeTwoColUp(2, 4, 100, 50); //Swipe UP
  delay(500); //Pause
  fastSwipeTwoColDown(2, 4, 100, 50); //Swipe DOWN
}

void liftDropShoulders() {
  fastSwipeTwoColUp(0,2,2,4,100,50); //Swipe UP on shoulders
  delay(400); //Pause
  fastSwipeTwoColDown(0,2,2,4,100,50); //Swipe DOWN on shoulders
  delay(500); //Pause
  fastSwipeTwoColUp(0,2,2,4,100,50); //Repeat
  delay(400);
  fastSwipeTwoColDown(0,2,2,4,100,50);
}

void turnHead() {
  fastSwipeLeftToRight(0,1,1,5,100,50);
  delay(500);
  fastSwipeRightToLeft(0,1,1,5,100,50);
}

void turnHips() {
  fastSwipeLeftToRight(5,6,1,5,100,50);
  delay(500);
  fastSwipeRightToLeft(5,6,1,5,100,50);
}

void dragonBreath(byte bottom, byte top) {
  if (bottom >= sizeof(rowPins)) {
    bottom = sizeof(rowPins) - 1;
  }  
  if (top < 0) {
    top = 0;
  }
  
  for (int i = bottom; i > bottom/2; i--) { //in
    resetPins();
	//fastSwipeTwoColUp(0, 2, 2, 4, 400, 50); //Repeat
	pckge_rowOn(i);
    delay(100);
  }

  resetPins();
  delay(400); 

  for (int i = bottom/2; i >= top; i--) { //in
    resetPins();
	//fastSwipeTwoColUp(0, 2, 2, 4, 400, 50); //Repeat
	pckge_rowOn(i);
    delay(100);
  }

  resetPins();
  delay(400);
  swipeAllRowsTopToBottom(90, 40);
  resetPins(); // Turn all off when done
  delay(300);
}

void fourCountBreath(byte bottom, byte top) {
  if (bottom >= sizeof(rowPins)) {
    bottom = sizeof(rowPins) - 1;
  }  
  if (top < 0) {
    top = 0;
  }
  
  for (int i = bottom; i >= top; i--) { //inhale
    resetPins();
    pckge_rowOn(i);
    delay(350);
  }

  for (int j = 0; j < 3; j++) { //hold
    resetPins();
    delay(700);
    pckge_rowOn(top);
    delay(300);
  }
  resetPins();
  delay(700); 
  
  for (int i = top; i <= bottom; i++) { //exhale
    resetPins();
    pckge_rowOn(i);
    delay(350);
  }

  for (int j = 0; j < 2; j++) { //hold
    resetPins();
    delay(700);
    pckge_rowOn(bottom);
    delay(300);
  }
  resetPins(); // Turn all off when done
  delay(700); 
}
