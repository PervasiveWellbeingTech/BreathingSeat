/*
 * Below are methods for vibration patterns.
 * These are the "building blocks" of the vibrations we test.
 * Scroll to top to see description of each.
 * Author:
 * Date:
 */

#ifndef HapticSeat_h
#define HapticSeat_h
#include "Arduino.h"

 
void fastSwipeOneCol(int col, int dur_t, int delay_t);

void fastSwipeTwoColDown(byte col1, byte col2, int dur_t, int delay_t);
void fastSwipeTwoColUp(byte col1, byte col2, int dur_t, int delay_t);
void fastSwipeTwoColDown(byte row1, byte row2, byte col1, byte col2, int dur_t, int delay_t);
void fastSwipeTwoColUp(byte row1, byte row2, byte col1, byte col2, int dur_t, int delay_t);

void swipeAllRowsTopToBottom(int dur_t, int delay_t);
void swipeAllRowsBottomToTop(int dur_t, int delay_t);

void interestIng(int dur_t, int delay_t);

void rowTest(byte r);
void colTest(byte c);

void rowOn(byte row);
void colOn(byte col);

void rowOff(byte row);
void colOff(byte col);

void multiRowOn(byte startRow, byte endRow);
void multiColOn(byte startCol, byte endCol);

// Turn an entire row on
void pckge_rowOn(byte row);

//Turn an entire column on
void pckge_colOn(byte col);

// version 1 : Row -> Col
void singleton(byte row, byte col);

// version 2 : Col -> Row

void resetRowsExceptFor(int row);
void resetRowsExceptFor(byte row1, byte row2);
void resetRowsExceptForRegion(byte row1, byte row2);
void resetColsExceptFor(int col);
void resetColsExceptFor(byte col1, byte col2);
void resetColsExceptForRegion(byte col1, byte col2);

void region(byte row1, byte row2, byte col1, byte col2);

// Turns off ALL LEDs
void resetPins();

void fastSwipeLeftToRight(byte row1, byte row2, byte col1, byte col2, int dur_t, int delay_t);
void fastSwipeRightToLeft(byte row1, byte row2, byte col1, byte col2, int dur_t, int delay_t);

// wait_ms is the time between switching from one row/colum to another. 
// use a lower value to get the animation to go faster.
void swipeLeftToRight(int wait_ms);
// wait_ms is the time between switching from one row/colum to another.
//use a lower value to get the animation to go faster.
void swipeRightToLeft(int wait_ms);
void swipeTopToBottom(int wait_ms);
void swipeBottomToTop(int wait_ms);

/* Experimental Sesh */
/* (newly added features) */

void testCol(int time);
void testRow(int time);

void action_cross(int wait_ms);

void everySingleOne(int wait_ms);

int getValueAt(int row, int col);

void swipeUShaped(int wait_ms);

#endif
