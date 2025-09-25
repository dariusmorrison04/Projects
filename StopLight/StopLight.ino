//Darius Morrison
//Stop light code
#include <LiquidCrystal.h> //Adds Liquid Crystal library.

#define GREEN_RED 0 //Define first state in finite state machine. Traffic light green, pedestrian light red. (0 is the index number)
#define YELLOW_RED 1 //The traffic light is yellow and pedestrian light is red.
#define RED_RED 2 //The traffic light is red and pedestrian light is red.
#define RED_GREEN 3 //The traffic light is red and pedestrian light is green.
#define RED_FLASHRED 4 //The traffic light is red and pedestrian light is flashing red.
#define RED_SOLIDRED 5 //The traffic light is red and pedestrian light is red.
#define WAIT 6 //Ensure the button cannot be pressed for 60 seconds.

LiquidCrystal lcd( A5, A4, 5, 6, 7, 8 ); //Declare which pins are used in LCD.
int state = GREEN_RED; //Declare variable 'state' that begins at the state GREEN_RED.
unsigned long timer_long; //Create an unsigned long to keep track of time for 30 seconds.
unsigned long timer_short; //Create an unsigned long to keep track of time for 5 seconds.
unsigned long timer_count; //Designate an unsigned long to count down from 30 every second.
unsigned long timer_flash; //Designate an unsigned long to count 0.5 seconds for the flashing red light.
int count = 30; //Declare variable count that begins with the number 30.

void setup() {
  pinMode( 9, OUTPUT ); //Set pin 9 to output, this is the green traffic led.
  pinMode( 10, OUTPUT ); //Designate pin 10 as output, this is the yellow traffic led.
  pinMode( 11, OUTPUT ); //Set pin 11 to output, this is the red traffic led.
  pinMode( 12, OUTPUT ); //Green pedestrian light.
  pinMode( 13, OUTPUT ); //Red pedestrian light.

  lcd.begin( 16, 2 ); //Declares the array of the LCD to be 16 by 2.
  lcd.clear(); //Clears the screen of LCD to set up for loop.
}

void loop() //Code to be looped.
{
 switch( state ) // Switch-Case statement for stoplight FSM. 
 {
  case GREEN_RED: //First case.
    if ( digitalRead( 4 ) == LOW ) //If the button is pressed.
  {
    state = YELLOW_RED; //Transfer states to YELLOW_RED.
    timer_short = millis(); //Set timer to milliseconds.
  }
  else //When the button is not pressed.
  {
    digitalWrite( 9, HIGH ); //Turn green traffic light on (stays on until button is pressed).
    digitalWrite( 13, HIGH ); //Turn red pedestrian light on (once again stays on until button is pressed).

    lcd.setCursor( 3, 0 ); //Places the cursor at point 4,1 (row, column).
    lcd.print ( "Don't Walk" ); //Prints 'Don't Walk' on the lCD screen.
  }
    break; //Ends this case.

  case YELLOW_RED: //Second case.
  {
   if ( ( millis() - timer_short ) < 5000 ) //If the timer is below 5 seconds.
   {
    digitalWrite( 9, LOW ); //Sets the green traffic light to off.
    digitalWrite( 10, HIGH ); //Turns on the yellow traffic light.
    lcd.setCursor( 3, 0 ); 
    lcd.print( "   Wait    " ); //Prints 'Wait' on the LCD screen with spaces to center.
   }
   else //If timer is at or past 5 seconds.
   {
    state = RED_RED; //Transition states to RED_RED.
    timer_short = millis(); //Declares timer_short to be in milliseconds.
   }
  }
  break; //Ends this case.

  case RED_RED: //Third case.
  {
    if ( ( millis() - timer_short ) < 5000 ) //If timer is below 5 seconds.
    {
    digitalWrite( 10, LOW ); //Sets the yellow traffic light to off.
    digitalWrite( 11, HIGH ); //Turns on the red traffic light.
    }
    else //When timer is at 5 seconds.
    {
      state = RED_GREEN; //Change states to RED_GREEN.
      timer_long = millis(); //Sets timer_long to be in milliseconds.
      timer_count = millis();
      count = 30; //Ensure count is set to 30.
    }
  }
  break; //Ends this case.

  case RED_GREEN: //Fourth case.
  {
    if( ( millis() - timer_long ) < 30000 ) //While the timer is below 30 seconds.
    {
      digitalWrite( 13, LOW ); //Turns off the red pedestrian light.
      digitalWrite( 12, HIGH ); //Turns on the green pedestrian light.

      lcd.setCursor( 3, 0 ); //Resets the cursor to point (4,1).
      lcd.print( "   Walk     "); //Prints Walk on the LCD. 

      if ( ( millis() - timer_count ) <= 1000 ) //While timer is below a second
      {
        if ( count >= 10) //If count is greater than or equal to 10.
        {
          lcd.setCursor( 7, 1 ); //Resets the cursor to point (8,2) on the LCD.
          lcd.print( count ); //Displays the count on the screen.
          count --; //Subtracts one off of count every second.
          timer_count += 1000; //Resets timer count.
        }
        else //When count is less than 10
        {
          lcd.clear(); //Clear the lcd screen
          lcd.setCursor( 3, 0 ); //Resets the cursor to (4,1).
          lcd.print( "   Walk     "); //Prints 'Walk' on the LCD every loop (probably unnecessary).

          lcd.setCursor( 8, 1 ); //Sets the cursor on the LCD to (9,2) making the count easier to read.
          lcd.print( count ); //Displays the count.
          count --; //Subtracts the count by 1. Decreasing every second.
          timer_count += 1000; //Resets timer count.
        }
      }
    }
    else //When timer passes 30 seconds.
    {
      state = RED_FLASHRED; //Switch states to RED_FLASHRED.
      timer_short = millis(); 
      timer_flash = millis();
    }
  }
    break; //Ends this case.

  case RED_FLASHRED: //Fifth case.
  {
  digitalWrite( 12, LOW ); //Sets the green pedestrian light off.

  if ( ( millis() - timer_short) < 5000) //If timer is below 5 seconds.
  {
    if ( ( millis() - timer_flash ) >= 500) //If flash timer is past 0.5 seconds.
    {
      timer_flash += 500; //Resets the flash timer.

      if ( digitalRead( 13 ) == LOW ) //If the pedestrian red light is off.
      {
        digitalWrite( 13, HIGH ); //Turn on red pedestrian light.
        lcd.clear(); //Clear LCD screen.
        lcd.setCursor( 3, 0 ); //Resets cursor to (4,1).
        lcd.print( "Don't Walk " ); //Prints 'Don't Walk' on the LCD screen.
      } 
      else //If pedestrian red light is on.
      {
        digitalWrite( 13, LOW ); //Turn off red pedestrian light.
        lcd.clear(); //Clear the LCD screen (creates a flashing effect every 0.5 seconds).
      }
    }
  }
    else //When timer is at or past 5 seconds.
    {
      state = RED_SOLIDRED; //Move state to RED_SOLIDRED.
      timer_short = millis(); //Declare short timer to be in milliseconds.
    }
  }
    break; //Ends this case.

  case RED_SOLIDRED: //Sixth case.
  {
    if ( ( millis() - timer_short ) <= 5000) //While timer is below 5 seconds.
    {
      digitalWrite( 13, HIGH); //Ensures that the red pedestrian light is on from last state.
      lcd.setCursor( 3, 0 ); 
      lcd.print( "Don't Walk " );
    }
    else //When timer passes 5 seconds.
    {
      state = WAIT; //Transition to wait state.
      timer_long = millis(); //Set long timer to be in milliseconds.
    }
  }
    break; //Ends this case.

  case WAIT: //Seventh and final case.
  {
    if ( ( millis() - timer_long ) < 10000) //If timer is less than 10 seconds. (This ensures the button cannot be pressed for a total of 60 seconds)
    {
      digitalWrite( 11, LOW ); //Turns off red traffic light.
      digitalWrite( 9, HIGH ); //Turns on green traffis light.
    }
    else
    {
      state = GREEN_RED; //Resets back to initial state.
    }
  }
    break; //Ends this case.

  default: state = GREEN_RED; //If something goes wrong, reset to first inital state.
 }

}
