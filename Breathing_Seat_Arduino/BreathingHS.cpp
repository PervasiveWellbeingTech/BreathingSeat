/*
 * 
 * Author: Nur Hamdan
 * Date: Non. 19, 2016
 */

 
#include "Arduino.h"
#include "HapticSeat.h"
#include "BreathingHS.h"

// 2-dimensional array of row pin numbers:
const byte colPins[7] = {2, 3, 4, 5, 6, 7, A1};
// 2-dimensional array of column pin numbers:
const byte rowPins[7] = {8, 9, 10, 11, 12, 13, A0};

void swipeFromColToCol(int startCol, int endCol, int startRow, int endRow, int duration, bool gradual) //NOT TESTED
{
  int switchDelay = 0;
  int steps = 0;
  int gradualDelay = 0;
  if (gradual)
  {
    switchDelay = 10;
    steps = abs(endCol-startCol);
    gradualDelay = (duration - (10*(steps-1)))/steps;
  }
  
  if ((startRow >=0 || startRow < sizeof(rowPins)) && (endRow >=0 || endRow < sizeof(rowPins)))
  {
    if ((startCol >=0 || startCol < sizeof(colPins)) && (endCol >=0 || endRow < sizeof(colPins)))
    {     
      for (int i = min(startRow,endRow); i <= max(startRow,endRow); i++)
      {
        digitalWrite(rowPins[i], HIGH);
      }

      if (startCol <= endCol) //left to right
      {
         for (int i = startCol; i <= endCol; i++)
        {
          resetColsExceptFor(i);
          delay(gradualDelay);
          if (i == endCol){ colOff(i); return;}
          resetColsExceptFor(i,i+1);
          delay(switchDelay);
        }    
      }
      else
      {
        for (int i = endCol; i >= startCol; i--) //right to left
        {
          resetColsExceptFor(i);
          delay(gradualDelay);
          if (i == startCol){ colOff(i); return;}
          resetColsExceptFor(i-1,i);
          delay(switchDelay);
        } 
      }
      resetPins(); 
    }
  }
}

void swipeFromRowToRow(int startRow, int endRow, int startCol, int endCol, int duration) //NOT TESTED
{
  int switchDelay = 10;
  int steps = abs(startRow-endRow);
  int gradualDelay = (duration - (10*(steps-1)))/steps;
  
  if ((startRow >=0 || startRow < sizeof(rowPins)) && (endRow >=0 || endRow < sizeof(rowPins)))
  {
    if ((startCol >=0 || startCol < sizeof(colPins)) && (endCol >=0 || endRow < sizeof(colPins)))
    {     
      for (int i = min(startCol,endCol); i <= max(startCol,endCol); i++)
      {
        digitalWrite(colPins[i], LOW);
      }

      if (startRow <= endRow) //left to right
      {
         for (int i = startRow; i <= endRow; i++)
        {
          resetColsExceptFor(i);
          delay(gradualDelay);
          if (i == endRow){ rowOff(i); return;}
          resetColsExceptFor(i,i+1);
          delay(switchDelay);
        }    
      }
      else
      {
        for (int i = endRow; i >= startRow; i--) //right to left
        {
          resetColsExceptFor(i);
          delay(gradualDelay);
          if (i == startRow){ rowOff(i); return;}
          resetColsExceptFor(i-1,i);
          delay(switchDelay);
        } 
      }
      resetPins(); 
    }
  }
}

void breathOutAccordion(int breathDuration)
{
    digitalWrite(rowPins[2], HIGH);
    digitalWrite(rowPins[3], HIGH);
    digitalWrite(rowPins[4], HIGH);
    digitalWrite(rowPins[5], HIGH);

    int bdelay = breathDuration/23;
    int dl = bdelay*4;
    int ds = bdelay;

    //4 dl (1 dl = 4 ds) + 3 ds = 23
    resetColsExceptFor(0,6);
    delay(dl);
    colOn(1);
    colOn(5);
    delay(ds);
    resetColsExceptFor(1,5);
    delay(dl);
    colOn(2);
    colOn(4);
    delay(ds);
    resetColsExceptFor(2,4);
    delay(dl);
    colOn(3);
    delay(ds);
    resetColsExceptFor(3);
    delay(dl);
    resetPins();
}

void breathInAccordion(int breathDuration)
{
    digitalWrite(rowPins[2], HIGH);
    digitalWrite(rowPins[3], HIGH);
    digitalWrite(rowPins[4], HIGH);
    digitalWrite(rowPins[5], HIGH);

    //4 dl (1 dl = 4 ds) + 3 ds = 23
    int bdelay = breathDuration/23;
    int dl = bdelay*5;
    int ds = bdelay;
    
    resetColsExceptFor(3);
    delay(dl);
    colOn(2);
    colOn(4);
    delay(ds);
    resetColsExceptFor(2,4);
    delay(dl);
    colOn(1);
    colOn(5);
    delay(ds);
    resetColsExceptFor(1,5);
    delay(dl);
    colOn(0);
    colOn(6);
    delay(ds);
    resetColsExceptFor(0,6);
    delay(dl);
    resetPins();
}

void breathInSwipUp(int breathDuration)
{
    digitalWrite(colPins[1], LOW);
    digitalWrite(colPins[2], LOW);
    digitalWrite(colPins[3], LOW);
    digitalWrite(colPins[4], LOW);
    digitalWrite(colPins[5], LOW);

    int bdelay = breathDuration/33;
    int dl = bdelay*5;
    int ds = bdelay;
    
    resetRowsExceptFor(5);
    delay(dl);
    rowOn(4);
    delay(dl);
    rowOn(3);
    delay(ds);
    resetRowsExceptFor(3,4);
    delay(dl);
    rowOn(2);
    delay(ds);
    resetRowsExceptFor(2,3);
    delay(dl);
    rowOn(1);
    delay(ds);
    resetRowsExceptFor(1,2);
    delay(dl);
    resetRowsExceptFor(1);
    delay(dl);
    resetPins();
}

void breathOutSwipDown(int breathDuration)
{
    digitalWrite(colPins[1], LOW);
    digitalWrite(colPins[2], LOW);
    digitalWrite(colPins[3], LOW);
    digitalWrite(colPins[4], LOW);
    digitalWrite(colPins[5], LOW);

    int bdelay = breathDuration/33;
    int dl = bdelay*5;
    int ds = bdelay;
    
    resetRowsExceptFor(1);
    delay(dl);
    rowOn(2);
    delay(dl);
    rowOn(3);
    delay(ds);
    resetRowsExceptFor(2,3);
    delay(dl);
    rowOn(4);
    delay(ds);
    resetRowsExceptFor(3,4);
    delay(dl);
    rowOn(5);
    delay(ds);
    resetRowsExceptFor(4,5);
    delay(dl);
    resetRowsExceptFor(5);
    delay(dl);
    resetPins();
  
}

void breathSpotN(int breathDuration, int row)
{
  int ds = 300; 
  digitalWrite(colPins[3], LOW);
  rowOn(row);
  delay(ds);
  resetPins();
  delay(breathDuration-ds); 
  resetPins();
}

void breathSpotC(int breathDuration, int row)
{
  digitalWrite(colPins[3], LOW);
  rowOn(row);
  delay(breathDuration);
  resetPins();
}

void breathSpotG(int breathDuration, int row)
{
  int ds = 200;
  int numOfVibrations = 3; //Should be based on bpm
  int bdelay = breathDuration/(numOfVibrations);

  digitalWrite(colPins[3], LOW);
  for (int i = 0; i < numOfVibrations; i++) {
    rowOn(row);
    delay(ds);
    rowOff(row);
    delay(bdelay);
  }
  resetPins();
}

/*
 * height is given as an int of value 0, 1, or 1. 2 representing short,
 * 1 representing medium, and 0 representing tall.
 * By Maddy Bernstein
 */
void breathInStrokeUp_Height(int breathDuration, int height)
{

    digitalWrite(colPins[3], LOW);

    int bdelay = breathDuration/11;
    int dl = bdelay*7;
    int ds = bdelay;

    resetRowsExceptFor(4 + height);
    
    for(int i = 3; i >= 0; i --) {
    	delay(ds);
    	rowOn(i + height);
    	resetRowsExceptFor(i + height);
    }
    delay(dl);
    resetPins();
}

/*
 * height is given as an int of value 0, 1, or 2. 2 representing short,
 * 1 representing medium, and 0 representing tall.
 * By Maddy Bernstein
 */
void breathOutStrokeDown_Height(int breathDuration, int height)
{
   
    digitalWrite(colPins[3], LOW);

    int bdelay = breathDuration/11;
    int dl = bdelay*7;
    int ds = bdelay;

 	resetRowsExceptFor(0 + height);
    
    for(int i = 1; i <= 4; i ++) {
    	delay(ds);
    	rowOn(i + height);
    	resetRowsExceptFor(i + height);
    }

    delay(dl);
    resetPins();
  
}

void breathInStrokeUp(int breathDuration)
{

    digitalWrite(colPins[3], LOW);

    int bdelay = breathDuration/15;
    int dl = bdelay*7;
    int ds = bdelay;
    
    resetRowsExceptFor(5);
    delay(ds);
    rowOn(4);
    delay(ds);
    rowOn(3);
    delay(ds);
    resetRowsExceptFor(3,4);
    delay(ds);
    rowOn(2);
    delay(ds);
    resetRowsExceptFor(2,3);
    delay(ds);
    rowOn(1);
    delay(ds);
    resetRowsExceptFor(1,2);
    delay(ds);
    resetRowsExceptFor(1);
    delay(dl);
    resetPins();
}

void breathOutStrokeDown(int breathDuration)
{
   
    digitalWrite(colPins[3], LOW);

    int bdelay = breathDuration/15;
    int dl = bdelay*7;
    int ds = bdelay;
    
    resetRowsExceptFor(1);
    delay(ds);
    rowOn(2);
    delay(ds);
    rowOn(3);
    delay(ds);
    resetRowsExceptFor(2,3);
    delay(ds);
    rowOn(4);
    delay(ds);
    resetRowsExceptFor(3,4);
    delay(ds);
    rowOn(5);
    delay(ds);
    resetRowsExceptFor(4,5);
    delay(ds);
    resetRowsExceptFor(5);
    delay(dl);
    resetPins();
  
}

void breathInSpiral(int breathDuration) 
{
  int ds = breathDuration/31;
  
  digitalWrite(colPins[3], LOW);
  resetRowsExceptFor(3);// 3,3
  delay(ds); 
  rowOn(2);//3,3 2,3
  delay(ds);
  colOn(2);//3,3 2,3 2,2 3,2
  delay(ds);
  colOff(3);//2,2 3,2
  delay(ds);
  rowOn(4);//2,2 3,2 4,2
  delay(ds);
  resetRowsExceptFor(4);//4,2
  delay(ds);
  colOn(3);//4,2 4,3 
  delay(ds);
  colOn(4);//4,2 4,3 4,4
  delay(ds);
  resetColsExceptFor(4);//4,4, 3,4 2,4
  delay(ds);
  resetRowsExceptFor(2);//2,4
  delay(ds);
  colOn(1);//2,1
  delay(ds);
  resetColsExceptFor(1); delay(ds);
  rowOn(3); delay(ds);
  rowOff(2); delay(ds);
  rowOn(4); delay(ds);
  rowOff(3); delay(ds);
  rowOn(5); delay(ds);
  rowOff(4); delay(ds);
  resetColsExceptFor(2); delay(ds);
  resetColsExceptFor(2,3); delay(ds);
  resetColsExceptFor(3); delay(ds);
  resetColsExceptFor(3,4); delay(ds);
  resetColsExceptFor(4); delay(ds);
  resetColsExceptFor(4,5); delay(ds);
  resetColsExceptFor(5); delay(ds);
  resetRowsExceptFor(4,5); delay(ds);
  resetRowsExceptFor(4); delay(ds);
  resetRowsExceptFor(3,4); delay(ds);
  resetRowsExceptFor(3); delay(ds);
  resetRowsExceptFor(2,3); delay(ds);
  resetRowsExceptFor(2); delay(ds);
  resetPins();
}

void breathOutSpiral() //NOT TESTED
{
  int ds = 100;
  
  digitalWrite(colPins[3], LOW);
  resetRowsExceptFor(3); delay(ds); 
  rowOn(2); delay(ds);
  colOn(2); delay(ds);
  colOff(3); delay(ds);
  rowOn(4); delay(ds);
  resetRowsExceptFor(4); delay(ds);
  colOn(3); delay(ds);
  colOn(4); delay(ds);
  resetColsExceptFor(4); delay(ds);
  resetRowsExceptFor(2); delay(ds);
  colOn(1); delay(ds);
  resetColsExceptFor(1); delay(ds);
  rowOn(3); delay(ds);
  rowOff(2); delay(ds);
  rowOn(4); delay(ds);
  rowOff(3); delay(ds);
  rowOn(5); delay(ds);
  rowOff(4); delay(ds);
  
  
  resetRowsExceptFor(2); delay(ds);
  resetRowsExceptFor(2,3); delay(ds);
  resetRowsExceptFor(3); delay(ds);
  resetRowsExceptFor(3,4); delay(ds);
  resetRowsExceptFor(4); delay(ds);
  resetRowsExceptFor(4,5); delay(ds);
  resetColsExceptFor(5); delay(ds);
  resetColsExceptFor(4,5); delay(ds);
  resetColsExceptFor(4); delay(ds);
  resetColsExceptFor(3,4); delay(ds);
  resetColsExceptFor(3); delay(ds);
  resetColsExceptFor(2,3); delay(ds);
  resetColsExceptFor(2); delay(ds);



  resetPins();
}


void breathInFlower(int breathDuration) 
{
    int ds = breathDuration/5;
    digitalWrite(colPins[3], LOW);
    resetRowsExceptFor(3);// 3,3
    delay(ds);
    rowOn(2);rowOn(4);
    colOn(2);colOn(4);
    delay(ds);
    colOff(3);
    delay(ds);
    rowOn(1);rowOn(5);
    colOn(1);colOn(5);
    delay(ds);
    rowOff(2);rowOff(4);
    colOff(2);colOff(4);
    delay(ds);
    resetPins();
}

void breathOutFlower(int breathDuration) 
{
    int ds = breathDuration/5;
    digitalWrite(colPins[3], LOW);
    rowOn(1);rowOn(5);
    colOn(1);colOn(5);
    delay(ds);
    rowOn(2);rowOn(4);
    colOn(2);colOn(4);
    delay(ds);
    rowOff(1);rowOff(5);
    colOff(1);colOff(5);
    delay(ds);
    rowOn(3);
    delay(ds);
    rowOff(2);rowOff(4);
    colOff(2);colOff(4);
    delay(ds);
    resetPins();
}

void testBreathing(int breathDuration) {
	int ds = breathDuration/5;
	digitalWrite(colPins[3], LOW);

	//colOn(6);
	rowOn(3);
	delay(4*ds);
	rowOff(3);
}
    

