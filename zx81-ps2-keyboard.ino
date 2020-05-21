
#include <ps2dev.h>    //Emulate a PS/2 device
#include "scancodes.h"

PS2dev kb(3,2);  //clock, data

unsigned long timecount = 0;

/*  x = 21,20,19,18,15
 *  y = 14,16,10,9,8,7,6,5
*/

const int cols[] = { A3, A2, A1, A0, 15 };
const int rows[] = { 14, 16, 10, 5, 6, 7, 8, 9 };

int colCounter;
int rowCounter;

int button_down[ZX_ROWS][ZX_COLS];

const int debounce_count = 3;

const int pause_time = 50;

// ScanCodes PressKey = TWO;




void setup() {
  kb.keyboard_init();
  Serial.begin(9600);
//  pinMode(LED_BUILTIN, OUTPUT);
  colCounter = 0;
  rowCounter = 0;
  for (int r = 0; r < 8; r++) {
	  for (int c = 0; c < 5; c++) {
		  button_down[r][c] = 0;
	  }

  }
  //rows are inputs and cols are outputs (for now at least)
  for (int r = 0; r < 8; r++) 
  {
    pinMode(rows[r], INPUT);
    digitalWrite(rows[r], LOW);
  }
  for (int c = 0; c < 5; c++) 
  {
    pinMode(cols[c], OUTPUT);
    digitalWrite(cols[c], LOW);
  }
}

void loop() 
{
  //Handle PS2 communication and react to keyboard led change
  //This should be done at least once each 10ms
  unsigned char leds;
  if(kb.keyboard_handle(&leds)) 
  {
    //Serial.print('LEDS');
    //Serial.print(leds, HEX);
    //digitalWrite(LED_BUILTIN, leds);
  }


// *** ok, so first pass of col 0 is not going to get any keypresses because all cols are low. Not duping code here.
//  // set the keys column to high.
//  digitalWrite(cols[colCounter], HIGH);
//  //might want a small wait here...
//  delay(pause_time);

  // check if key is being pressed. (i.e. check if keys row state. is high)
  if (digitalRead(rows[rowCounter]) == HIGH) // is it is pressed?
  { //pressed
	  button_down[rowCounter][colCounter]++; // increment its counter
	  if (button_down[rowCounter][colCounter] == debounce_count)
	  {
		  kb.keyboard_press(zx81_map[rowCounter][colCounter]); // report key pressed
		  Serial.print(rowCounter);
		  Serial.print(", ");
		  Serial.println(colCounter);
      Serial.flush();
	  }
  }
  else
  { //not pressed
	  if (button_down[rowCounter][colCounter] >= debounce_count)
		  kb.keyboard_release(zx81_map[rowCounter][colCounter]); // report keyup
	  button_down[rowCounter][colCounter] = 0; // set counter to 0
  }

  // end of processing for this button, select the next one
  rowCounter++;
  if (rowCounter == ZX_ROWS)
  {
    rowCounter = 0;
    // set the col back to LOW.
    digitalWrite(cols[colCounter], LOW);
    colCounter++;
    if (colCounter == ZX_COLS)
    {
      colCounter = 0;
      delay(pause_time);
    };
    digitalWrite(cols[colCounter], HIGH);
  }
 
//    Serial.flush();

  //Print letter every second
//  if((millis() - timecount) > 1000) {
//    kb.keyboard_mkbrk(PressKey); //Make + Break key
//    Serial.print('.');
//    timecount = millis();
//  }

}
